package com.android.support;

import android.content.Context;
import android.util.Base64;

import com.topjohnwu.superuser.Shell;
import java.util.ArrayList;
import java.util.List;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

class Utils {
    	public static int getProcessID(String pkg) {
 
        int pid = -1;
        if (Shell.rootAccess()) {
            String cmd = "for p in /proc/[0-9]*; do [[ $(<$p/cmdline) = " + pkg + " ]] && echo ${p##*/}; done";
            List<String> outs = new ArrayList<>();
            Shell.su(cmd).to(outs).exec();
            if (outs.size() > 0) {
                pid = Integer.parseInt(outs.get(0));
            }
        } else {
            Shell.Result out = Shell.sh("/system/bin/ps -A | grep \"" + pkg + "\"").exec();
            List<String> output = out.getOut();
            if (output.isEmpty() || output.get(0).contains("bad pid")) {
                out = Shell.sh("/system/bin/ps | grep \"" + pkg + "\"").exec();
                output = out.getOut();
                if (!output.isEmpty() && !output.get(0).contains("bad pid")) {
                    for (int i = 0; i < output.size(); i++) {
                        String[] results = output.get(i).trim().replaceAll("( )+", ",").replaceAll("(\n)+", ",").split(",");
                        if (results[8].equals(pkg)) {
                            pid = Integer.parseInt(results[1]);
                        }
                    }
                }
            } else {
                for (int i = 0; i < output.size(); i++) {
                    String[] results = output.get(i).trim().replaceAll("( )+", ",").replaceAll("(\n)+", ",").split(",");
                    for (int j = 0; j < results.length; j++) {
                        if (results[j].equals(pkg)) {
                            pid = Integer.parseInt(results[j - 7]);
                        }
                    }
                }
            }
        }
        return pid;
    }

    private static String bytesToHex(byte[] bytes) {
        char[] hexArray = "0123456789abcdef".toCharArray();
        char[] hexChars = new char[bytes.length * 2];
        for (int j = 0; j < bytes.length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = hexArray[v >>> 4];
            hexChars[j * 2 + 1] = hexArray[v & 0x0F];
        }
        return new String(hexChars);
    }

    static String readStream(InputStream in) throws IOException{
        StringBuilder response = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
            String line = "";
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
		}
        return response.toString();
    }

    static String SHA256(String data) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.reset();
            md.update(data.getBytes(StandardCharsets.UTF_8));
            return bytesToHex(md.digest()).toUpperCase();
        } catch (NoSuchAlgorithmException ex) {
            return null;
        }
    }

    static void clearCache(Context context) {
        try {
            File dir = context.getCacheDir();
            deleteFilesInDir(dir);
        } catch (Exception ignored) {}
    }

    private static void deleteFilesInDir(File dir) {
        for (File file: dir.listFiles()) {
            if (file.isDirectory()) {
                deleteFilesInDir(file);
            }
            file.delete();
        }
    }

    static byte[] loaderDecrypt(byte[] srcdata){
        try {
            SecretKeySpec skey = new SecretKeySpec("22P9ULFDKPJ70G46".getBytes(), "AES");
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, skey);
            return cipher.doFinal(srcdata);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        }
        return null;
    }

    static String profileDecrypt(String data, String sign) {
        char[] key = sign.toCharArray();
        char[] out = fromBase64String(data).toCharArray();
        for(int i = 0; i < out.length;i++){
            out[i] = (char)(key[i % key.length] ^ out[i]);
        }
        return new String(out);
    }

    static String toBase64(String s) {
        return Base64.encodeToString(s.getBytes(StandardCharsets.UTF_8), Base64.NO_WRAP);
    }

    static String toBase64(byte[] s) {
        return Base64.encodeToString(s, Base64.NO_WRAP);
    }

    static byte[] fromBase64(String s) {
        return Base64.decode(s, Base64.NO_WRAP);
    }

    static String fromBase64String(String s) {
        return new String(Base64.decode(s, Base64.NO_WRAP), StandardCharsets.UTF_8);
    }
}

