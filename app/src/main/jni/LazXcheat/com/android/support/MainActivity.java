package com.android.support;

import android.app.*;
import android.os.*;
import android.content.*;
import android.provider.*;
import android.net.*;
import android.widget.*;
import android.content.res.*;
import java.io.*;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings; 
import android.widget.Toast;
import com.topjohnwu.superuser.Shell;
import java.util.ArrayList;
import java.util.List;
import java.io.File;
import android.speech.tts.TextToSpeech;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;
import android.view.View;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URLDecoder;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
public class MainActivity extends Activity {
    private Intent makabasa = new Intent();
	static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        //System.loadLibrary("MyLibName");
    }

    //To call onCreate, please refer to README.md
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        makabasa.setAction(Intent.ACTION_VIEW);
        makabasa = getPackageManager().getLaunchIntentForPackage("com.dts.freefireth");
        startActivity(makabasa);
     if (InjectRoot("libmain.so")) {
     Toast.makeText(getApplicationContext(), "INJECT SUCCESS", Toast.LENGTH_LONG).show();
     DeletedCMODs("libmain.so");                                           
            }
        };    
    private boolean InjectRoot(String Lib) {
        try {
            String target = "com.dts.freefireth";
            String injector = this.getApplicationInfo().nativeLibraryDir + File.separator + "libcatchmeifyoucan.so";
            String payload_source = this.getApplicationInfo().nativeLibraryDir + File.separator + Lib;
            String payload_dest = "/dev/"+Lib;
            String context = "u:object_r:system_lib_file:s0";
            List<String> STDOUT = new ArrayList<>();
            Shell.su("ls -lZ /system/lib/libandroid_runtime.so").to(STDOUT).exec();
            for (String line : STDOUT) {
                if (line.contains(" u:object_r:") && line.contains(":s0 ")) {
                    context = line.substring(line.indexOf("u:object_r:"));
                    context = context.substring(0, context.indexOf(' '));
                }
            }
            Shell.su("cp " + payload_source + " " + payload_dest).exec();
            Shell.su("chmod 777 " + payload_dest).exec();
            Shell.su("chcon " + context + " " + payload_dest).exec();
            while (Utils.getProcessID(target) <= 0) {}
            Thread.sleep(1000);
            int pid = Utils.getProcessID(target);
          //  writeFile("/storage/emulated/0/getPid.txt",Integer.toString(pid));
           // Toast.makeText(this, pid, Toast.LENGTH_LONG).show();
            String command = String.format(Locale.ENGLISH,"%s %d %s", injector, pid, payload_dest);
            Shell.su(command).exec();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "INJECT FAILED PLEASE ROOT", Toast.LENGTH_LONG).show();
            return false;
        }
	}	
	public void DeletedCMODs(String remv) {
        cmods_exec("rm -rf " + "/dev/" + remv);      
        
        Toast.makeText(getApplicationContext(), "BYPASS SUCCESS", Toast.LENGTH_LONG).show();
        
    }
    public static int cmods_exec(String cmd) {
        int result = -1;
        DataOutputStream dos = null;

        try {
            java.lang.Process p = Runtime.getRuntime().exec("su");
            dos = new DataOutputStream(p.getOutputStream());
            dos.writeBytes(cmd + "\n");
            dos.flush();
            dos.writeBytes("exit\n");
            dos.flush();
            p.waitFor();
            result = p.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (dos != null) {
                try {
                    dos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return result;
    }
    private static void createNewFile(String path) {
        int lastSep = path.lastIndexOf(File.separator);
        if (lastSep > 0) {
            String dirPath = path.substring(0, lastSep);
            makeDir(dirPath);
        }

        File file = new File(path);

        try {
            if (!file.exists()) file.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static String readFile(String path) {
        createNewFile(path);

        StringBuilder sb = new StringBuilder();
        FileReader fr = null;
        try {
            fr = new FileReader(new File(path));

            char[] buff = new char[1024];
            int length = 0;

            while ((length = fr.read(buff)) > 0) {
                sb.append(new String(buff, 0, length));
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fr != null) {
                try {
                    fr.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }

        return sb.toString();
    }
    public static void writeFile(String path, String str) {
        createNewFile(path);
        FileWriter fileWriter = null;

        try {
            fileWriter = new FileWriter(new File(path), false);
            fileWriter.write(str);
            fileWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (fileWriter != null)
                    fileWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void copyFile(String sourcePath, String destPath) {
        if (!isExistFile(sourcePath)) return;
        createNewFile(destPath);

        FileInputStream fis = null;
        FileOutputStream fos = null;

        try {
            fis = new FileInputStream(sourcePath);
            fos = new FileOutputStream(destPath, false);

            byte[] buff = new byte[1024];
            int length = 0;

            while ((length = fis.read(buff)) > 0) {
                fos.write(buff, 0, length);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void copyDir(String oldPath, String newPath) {
        File oldFile = new File(oldPath);
        File[] files = oldFile.listFiles();
        File newFile = new File(newPath);
        if (!newFile.exists()) {
            newFile.mkdirs();
        }
        for (File file : files) {
            if (file.isFile()) {
                copyFile(file.getPath(), newPath + "/" + file.getName());
            } else if (file.isDirectory()) {
                copyDir(file.getPath(), newPath + "/" + file.getName());
            }
        }
    }

    public static void moveFile(String sourcePath, String destPath) {
        copyFile(sourcePath, destPath);
        deleteFile(sourcePath);
    }

    public static void deleteFile(String path) {
        File file = new File(path);

        if (!file.exists()) return;

        if (file.isFile()) {
            file.delete();
            return;
        }

        File[] fileArr = file.listFiles();

        if (fileArr != null) {
            for (File subFile : fileArr) {
                if (subFile.isDirectory()) {
                    deleteFile(subFile.getAbsolutePath());
                }

                if (subFile.isFile()) {
                    subFile.delete();
                }
            }
        }

        file.delete();
    }

    public static boolean isExistFile(String path) {
        File file = new File(path);
        return file.exists();
    }

    public static void makeDir(String path) {
        if (!isExistFile(path)) {
            File file = new File(path);
            file.mkdirs();
        }
    }

    public static void listDir(String path, ArrayList<String> list) {
        File dir = new File(path);
        if (!dir.exists() || dir.isFile()) return;

        File[] listFiles = dir.listFiles();
        if (listFiles == null || listFiles.length <= 0) return;

        if (list == null) return;
        list.clear();
        for (File file : listFiles) {
            list.add(file.getAbsolutePath());
        }
    }

    public static boolean isDirectory(String path) {
        if (!isExistFile(path)) return false;
        return new File(path).isDirectory();
    }
} 
