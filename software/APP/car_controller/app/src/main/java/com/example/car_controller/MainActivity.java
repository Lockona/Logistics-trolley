package com.example.car_controller;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.io.IOException;
import java.net.InetAddress;


public class MainActivity extends AppCompatActivity {
    Boolean isConnected = false;
    Boolean isChanged = false;
    Boolean changedPID = false;
    char cmd;
    Button connect_Button;
    Button forward_Button;
    Button backward_Button;
    Button button_pid;
    TextView angle_Text;
    TextView speed_Text;
    TextView rx_text;
    TextView ry_text;
    TextView rz_text;
    TextView p_text;
    TextView i_text;
    TextView d_text;
    TextView textView_b;
    SeekBar p_Bar;
    SeekBar i_Bar;
    SeekBar d_Bar;
    SeekBar angle_Bar;
    SeekBar speed_Bar;
    ProgressBar progressBar;
    Socket socket = null;
    private OutputStream outputStream = null;
    private InputStream inputStream = null;
    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controll);
        connect_Button = findViewById(R.id.button_conn);
        forward_Button = findViewById(R.id.button_up);
        backward_Button = findViewById(R.id.button_down);
        button_pid = findViewById(R.id.button_pid);
        angle_Text = findViewById(R.id.textView_angle);
        speed_Text = findViewById(R.id.textView_speed);
        rx_text = findViewById(R.id.textView_Rx);
        ry_text = findViewById(R.id.textView_Ry);
        rz_text = findViewById(R.id.textView_Rz);
        p_text = findViewById(R.id.textView_p);
        i_text = findViewById(R.id.textView_i);
        d_text = findViewById(R.id.textView_d);
        textView_b = findViewById(R.id.textView_b);
        p_Bar = findViewById(R.id.seekBar_p);
        i_Bar = findViewById(R.id.seekBar_i);
        d_Bar = findViewById(R.id.seekBar_d);
        speed_Bar = findViewById(R.id.seekBar_speed);
        angle_Bar = findViewById(R.id.seekBar_angle);
        progressBar = findViewById(R.id.progressBar);
        forward_Button.setEnabled(false);
        backward_Button.setEnabled(false);
        button_pid.setEnabled(false);
        p_Bar.setProgress(18);
        connect_Button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(isConnected == false) {
                    Connect_Thread connect_Thread = new Connect_Thread();
                    connect_Thread.start();
                }
                else
                {
                    isConnected =false;
                    connect_Button.setText("连接");
                    forward_Button.setEnabled(false);
                    backward_Button.setEnabled(false);
                    button_pid.setEnabled(false);
                    try {
                        socket.close();//关闭连接
                        socket = null;
                    }
                    catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        forward_Button.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN)
                {
                    isChanged = true;
                    cmd = 'F';
                }
                else if(motionEvent.getAction() == MotionEvent.ACTION_UP)
                {
                    isChanged = true;
                    cmd = 'S';
                }
                return false;
            }
        });
        backward_Button.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN)
                {
                    isChanged = true;
                    cmd = 'B';
                }
                else if(motionEvent.getAction() == MotionEvent.ACTION_UP)
                {
                    isChanged = true;
                    cmd = 'S';
                }
                return false;
            }
        });
        button_pid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                changedPID = true;
            }
        });
        angle_Bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if(isConnected) {
                    angle_Text.setText("" + (i-179));
                    isChanged = true;
                    cmd = 'A';
                }
                else
                    seekBar.setProgress(90);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        speed_Bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if(isConnected)
                    speed_Text.setText(""+i);
                else
                    seekBar.setProgress(20);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        p_Bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                p_text.setText(""+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        i_Bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                i_text.setText(""+((double)i/100));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        d_Bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                d_text.setText(""+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }
    class Connect_Thread extends Thread
    {
        public void run()//重写run方法
        {
            try
            {
                if (socket == null)
                {
                    socket = new Socket("192.168.4.1", 5000);
                    Send_Thread send_Thread = new Send_Thread();
                    send_Thread.start();
                    Receive_Thread receive_Thread = new Receive_Thread();
                    receive_Thread.start();
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
            if(socket.isConnected()) {
                isConnected = true;
                runOnUiThread(new Runnable()//不允许其他线程直接操作组件，用提供的此方法可以
                  {
                      public void run() {
                          forward_Button.setEnabled(true);
                          backward_Button.setEnabled(true);
                          button_pid.setEnabled(true);
                          connect_Button.setText("断开");
                      }
                  });

            }
        }
    }
    class Send_Thread extends Thread {
        public void run()//重写run方法
        {
            try {
                while (true) {
                    if(isChanged) {
                        isChanged = false;
                        String str = new String();
                        outputStream = socket.getOutputStream();
                        switch (cmd)
                        {
                            case 'F':
                                str = ('M' + speed_Text.getText().toString() + "\r\n");
                                break;
                            case 'B':
                                str = ('M' + Integer.toString(Integer.parseInt(speed_Text.getText().toString()) * -1) + "\r\n");
                                break;
                            case 'S':
                                str = ("M" + "0\r\n");
                                break;
                            case 'A':
                                Thread.sleep(100);
                                str = ('A' + angle_Text.getText().toString() + "\r\n");
                                System.out.println(str);
                                break;
                        }
                        outputStream.write(str.getBytes());
                        str = null;
                        Thread.sleep(10);
                    }
                    else if(changedPID) {
                        changedPID = false;
                        String str;
                        System.out.println("qw");
                        outputStream = socket.getOutputStream();
                        str = ("P" + p_text.getText().toString() + "\r\n");
                        outputStream.write(str.getBytes());
                        str = ("I" + i_text.getText().toString() + "\r\n");
                        outputStream.write(str.getBytes());
                        str = ("D" + d_text.getText().toString() + "\r\n");
                        outputStream.write(str.getBytes());
                        str = null;
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
    //接收线程
    class Receive_Thread extends Thread
    {
        public void run()//重写run方法
        {
            try
            {
                final byte[] buffer = new byte[128];//创建接收缓冲区
                while (true)
                {
                    inputStream = socket.getInputStream();
                    final int len = inputStream.read(buffer);//数据读出来，并且返回数据的长度
                    System.out.println("长度："+len);
                    runOnUiThread(new Runnable()//不允许其他线程直接操作组件，用提供的此方法可以
                        {
                            public void run()
                            {
                            try {
                                String str = new String(buffer,"UTF-8");
                                if (str.charAt(0) != 'B')
                                {
                                    String s[] = str.split(",");
                                    String s0[] = s[0].split("=");
                                    String s1[] = s[1].split("=");
                                    String s2[] = s[2].split("=");
                                    rx_text.setText(s0[1]);
                                    ry_text.setText(s1[1]);
                                    rz_text.setText(s2[1]);
                                }
                                else
                                {
                                    System.out.println(str);
                                    str = str.substring(0,str.indexOf(' '));
                                    System.out.println(str);
                                    String s[] = str.split(":");
                                    progressBar.setProgress(Integer.parseInt(s[1]));
                                    textView_b.setText(s[1]);
                                }
                            }
                            catch (UnsupportedEncodingException e)
                            {
                                e.printStackTrace();
                            }

                        }
                    });
                }
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }

        }
    }
}

