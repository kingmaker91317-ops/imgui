package com.android.support;
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

public class exec {
  static public boolean InjectVirtual(String Lib,Context con) {
        try {
            String target = "com.dts.freefireth";
            String injector = con.getApplicationInfo().nativeLibraryDir + File.separator + "libinject.so";
            String payload_source = con.getApplicationInfo().nativeLibraryDir + File.separator + Lib;
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
            String command = String.format(Locale.ENGLISH,"%s %d %s", injector, pid, payload_dest);
            Shell.su(command).exec();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
	}
    static public boolean InjectRoot(String Lib,Context con) {
        try {
            String target = "com.dts.freefireth";
            String injector = con.getApplicationInfo().nativeLibraryDir + File.separator + "libcatchmeifyoucan.so";
            String payload_source = con.getApplicationInfo().nativeLibraryDir + File.separator + Lib;
            String payload_dest = "/data/local/tmp/"+Lib;
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
            String command = String.format(Locale.ENGLISH,"%s %d %s", injector, pid, payload_dest);
            Shell.su(command).exec();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
	}
}
