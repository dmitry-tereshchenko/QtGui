package src.org;
import android.Manifest;
import android.os.Build;
import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.util.Log;
import android.content.pm.PackageManager;
import java.io.File;
import java.util.ArrayList;
import android.app.AlertDialog;
import android.content.DialogInterface;
import java.util.List;

public class RequestPermissions
{
    private static final int REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS = 116;
    private static String responseStateStr = "Unknown";  //  0 - "Unknown",  1 - "Granted",  2 - "Denied", 3 - "Just Granted"
    private final Activity m_MainActivity;
    public RequestPermissions(Activity MainActivity)
    {
        m_MainActivity = MainActivity;
        MainActivity.runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                askPermissions(m_MainActivity);
            }
        });
    }
    static String getResponseState() { return responseStateStr; }
    static String getSdkVersion()
    {
        return String.valueOf(android.os.Build.VERSION.SDK_INT);
    }

    public static void askPermissions(Activity currentActivity)
    {
        final List<String> permissionsList = new ArrayList<String>();

        if (currentActivity.checkCallingOrSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
            { permissionsList.add(Manifest.permission.READ_EXTERNAL_STORAGE); }

        if (currentActivity.checkCallingOrSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
            { permissionsList.add(Manifest.permission.WRITE_EXTERNAL_STORAGE); }

        final FragmentManager fragmentManager = currentActivity.getFragmentManager();
        final Fragment request = new Fragment() {
            @Override public void onStart()
            {
                super.onStart();
                if (!permissionsList.isEmpty())
                {
                    requestPermissions(permissionsList.toArray(new String[permissionsList.size()]), REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS);
                }
                else
                {
                    responseStateStr = "Granted";
                }
            }

            @Override public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
            {
                if (requestCode != REQUEST_CODE_ASK_MULTIPLE_PERMISSIONS) return;

                if ((grantResults.length > 0) && (grantResults[0] == PackageManager.PERMISSION_GRANTED))
                {
                    responseStateStr = "Just Granted";
                }

                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                fragmentTransaction.remove(this);
                fragmentTransaction.commit();
            }
        };

        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.add(0, request);
        fragmentTransaction.commit();
    }
}
