require('dotenv').config();
const express = require('express');
const cors = require('cors');
const path = require('path');
const { dbRun, dbGet, dbAll } = require('./database');

const app = express();
const PORT = process.env.PORT || 3000;
const ADMIN_KEY = process.env.ADMIN_KEY || 'LION_ADMIN_SECRET_123';

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

// Helper: Generate Random Key
function generateRandomKey(prefix = 'LION') {
    const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    let result = '';
    for (let i = 0; i < 4; i++) {
        for (let j = 0; j < 4; j++) {
            result += chars.charAt(Math.floor(Math.random() * chars.length));
        }
        if (i < 3) result += '-';
    }
    return `${prefix}-${result}`;
}

// Middleware: Admin Auth Check
function adminAuth(req, res, next) {
    const authHeader = req.headers['x-admin-key'] || req.query.admin_key || req.body.admin_key;
    if (!authHeader || authHeader !== ADMIN_KEY) {
        return res.status(401).json({ status: 'error', message: 'Unauthorized: Invalid Admin Secret Key' });
    }
    next();
}

// -------------------------------------------------------------
// 1. CLIENT VERIFICATION API (Used by C++ App)
// -------------------------------------------------------------
app.post('/api/verify', async (req, res) => {
    try {
        const { key, hwid } = req.body;

        if (!key) {
            return res.json({ status: 'error', message: 'User Key is required' });
        }

        const keyData = await dbGet('SELECT * FROM keys WHERE key = ?', [key.trim()]);

        if (!keyData) {
            return res.json({ status: 'error', message: 'Invalid Key! Please check and try again.' });
        }

        if (keyData.status === 'banned') {
            return res.json({ status: 'error', message: 'This Key has been BANNED by Admin!' });
        }

        const now = new Date();

        // If key hasn't been activated yet, activate it now!
        if (!keyData.expires_at) {
            const expDate = new Date();
            expDate.setDate(expDate.getDate() + parseInt(keyData.duration_days));
            
            await dbRun(
                'UPDATE keys SET expires_at = ?, hwid = ?, status = ? WHERE id = ?',
                [expDate.toISOString(), hwid || null, 'active', keyData.id]
            );

            return res.json({
                status: 'success',
                message: 'Key Activated Successfully!',
                expires_at: expDate.toISOString(),
                days_left: keyData.duration_days
            });
        }

        // Check Expiration
        const expirationDate = new Date(keyData.expires_at);
        if (now > expirationDate) {
            await dbRun('UPDATE keys SET status = ? WHERE id = ?', ['expired', keyData.id]);
            return res.json({ status: 'error', message: 'Your Key has EXPIRED!' });
        }

        // Check HWID Binding
        if (hwid && keyData.hwid && keyData.hwid !== hwid) {
            return res.json({ status: 'error', message: 'HWID Mismatch! Key is bound to another device.' });
        }

        // If HWID wasn't recorded before, bind it now
        if (hwid && !keyData.hwid) {
            await dbRun('UPDATE keys SET hwid = ? WHERE id = ?', [hwid, keyData.id]);
        }

        const msLeft = expirationDate.getTime() - now.getTime();
        const daysLeft = Math.ceil(msLeft / (1000 * 3600 * 24));

        return res.json({
            status: 'success',
            message: 'Key Verification Successful!',
            expires_at: keyData.expires_at,
            days_left: daysLeft
        });

    } catch (error) {
        console.error('Verify error:', error);
        return res.status(500).json({ status: 'error', message: 'Server Internal Error' });
    }
});

// -------------------------------------------------------------
// 2. ADMIN API ENDPOINTS (Web Panel)
// -------------------------------------------------------------

// Check Admin Login
app.post('/api/admin/login', (req, res) => {
    const { admin_key } = req.body;
    if (admin_key === ADMIN_KEY) {
        return res.json({ status: 'success', message: 'Authenticated' });
    }
    return res.status(401).json({ status: 'error', message: 'Invalid Admin Secret Key' });
});

// Get All Keys List & Stats
app.get('/api/admin/keys', adminAuth, async (req, res) => {
    try {
        const keys = await dbAll('SELECT * FROM keys ORDER BY id DESC');
        res.json({ status: 'success', keys });
    } catch (err) {
        res.status(500).json({ status: 'error', message: err.message });
    }
});

// Generate New Key
app.post('/api/admin/create-key', adminAuth, async (req, res) => {
    try {
        const { duration_days, note, custom_key } = req.body;
        const key = custom_key && custom_key.trim().length > 0 ? custom_key.trim() : generateRandomKey();
        const days = parseInt(duration_days) || 1;

        await dbRun(
            'INSERT INTO keys (key, duration_days, note, status) VALUES (?, ?, ?, ?)',
            [key, days, note || '', 'active']
        );

        res.json({ status: 'success', message: 'Key Created Successfully', key });
    } catch (err) {
        if (err.message.includes('UNIQUE')) {
            return res.json({ status: 'error', message: 'Key already exists! Choose a different custom key.' });
        }
        res.status(500).json({ status: 'error', message: err.message });
    }
});

// Reset HWID
app.post('/api/admin/reset-hwid', adminAuth, async (req, res) => {
    try {
        const { id } = req.body;
        await dbRun('UPDATE keys SET hwid = NULL WHERE id = ?', [id]);
        res.json({ status: 'success', message: 'HWID Reset Successfully' });
    } catch (err) {
        res.status(500).json({ status: 'error', message: err.message });
    }
});

// Ban / Unban Key
app.post('/api/admin/toggle-ban', adminAuth, async (req, res) => {
    try {
        const { id, status } = req.body;
        const newStatus = status === 'banned' ? 'active' : 'banned';
        await dbRun('UPDATE keys SET status = ? WHERE id = ?', [newStatus, id]);
        res.json({ status: 'success', message: `Key status updated to ${newStatus}` });
    } catch (err) {
        res.status(500).json({ status: 'error', message: err.message });
    }
});

// Delete Key
app.post('/api/admin/delete-key', adminAuth, async (req, res) => {
    try {
        const { id } = req.body;
        await dbRun('DELETE FROM keys WHERE id = ?', [id]);
        res.json({ status: 'success', message: 'Key Deleted' });
    } catch (err) {
        res.status(500).json({ status: 'error', message: err.message });
    }
});

// Serve Admin Panel
app.get('/admin', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'admin.html'));
});

app.listen(PORT, () => {
    console.log(`=================================`);
    console.log(`LION KEY AUTH SERVER ACTIVE`);
    console.log(`Port: ${PORT}`);
    console.log(`Admin Panel: http://localhost:${PORT}/admin`);
    console.log(`=================================`);
});
