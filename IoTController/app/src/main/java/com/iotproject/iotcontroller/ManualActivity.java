package com.iotproject.iotcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import static com.iotproject.iotcontroller.MainActivity.connectedThread;

public class ManualActivity extends AppCompatActivity {

    Button btn_sector1, btn_sector2, btn_sector3, btn_sector4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manual);

        btn_sector1 = (Button) findViewById(R.id.sector1);
        btn_sector2 = (Button) findViewById(R.id.sector2);
        btn_sector3 = (Button) findViewById(R.id.sector3);
        btn_sector4 = (Button) findViewById(R.id.sector4);
    }

    public void onClickButtonsector1(View view){
        if(connectedThread!=null){ connectedThread.write("Ctrl,00,@"); }
    }

    public void onClickButtonsector2(View view){
        if(connectedThread!=null){ connectedThread.write("Ctrl,01,@"); }
    }

    public void onClickButtonsector3(View view){
        if(connectedThread!=null){ connectedThread.write("Ctrl,02,@"); }
    }

    public void onClickButtonsector4(View view){
        if(connectedThread!=null){ connectedThread.write("Ctrl,03,@"); }
    }
}