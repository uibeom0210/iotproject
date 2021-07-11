package com.iotproject.iotcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import static com.iotproject.iotcontroller.MainActivity.connectedThread;

public class AutoActivity extends AppCompatActivity {

    TextView text_weather_info;
    Button btn_register1, btn_register2, btn_register3, btn_register4, btn_get_weather;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_auto);

        text_weather_info = (TextView) findViewById(R.id.weather_info);
        btn_register1 = (Button) findViewById(R.id.register1);
        btn_register2 = (Button) findViewById(R.id.register2);
        btn_register3 = (Button) findViewById(R.id.register3);
        btn_register4 = (Button) findViewById(R.id.register4);
        btn_get_weather = (Button) findViewById(R.id.get_weather);

    }

    public void onClickButtonregister1(View view){
        if(connectedThread!=null){ connectedThread.write("Select,00,@"); }
        //text_weather_info.setText("Select,00,@");
    }
    public void onClickButtonregister2(View view){
        if(connectedThread!=null){ connectedThread.write("Select,01,@"); }
    }
    public void onClickButtonregister3(View view){
        if(connectedThread!=null){ connectedThread.write("Select,02,@"); }
    }
    public void onClickButtonregister4(View view){
        if(connectedThread!=null){ connectedThread.write("Select,03,@"); }
    }


    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case Constants.MESSAGE_WRITE:
                    byte[] writeBuf = (byte[]) msg.obj;
                    // construct a string from the buffer
                    String writeMessage = new String(writeBuf);

                    break;
                case Constants.MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;
                    Toast.makeText(getApplicationContext(), "its okay", Toast.LENGTH_SHORT).show();
                    // construct a string from the valid bytes in the buffer
                    //String readMessage = new String(readBuf, 0, msg.arg1);
                    //text_weather_info.setText(readMessage);
                    break;
            }
        }
    };

    public void onClickButtongetweather(View view){
        if(connectedThread!=null){ connectedThread.write("View,weather,@"); }
        new Handler().postDelayed(new Runnable()
        {
            @Override
            public void run()
            {
                text_weather_info.setText(connectedThread.readMessage);
            }
        }, 3000);
    }
}