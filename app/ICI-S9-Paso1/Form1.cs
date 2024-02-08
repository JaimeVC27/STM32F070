using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ICI_S9_Paso1
{
    public partial class Form1 : Form
    {
        double temperatura, temperatura_remota;
        double velocidad, velocidad_remota;
        double posicion, posicion_remota;

        public Form1()
        {
            InitializeComponent();
            serialPort1.Encoding = System.Text.Encoding.GetEncoding("utf-8");
            serialPort1.Open();
            velocidad = 0;
            temperatura = 0;  //inicializamos
            serialPort1.DiscardInBuffer(); // Descarto todo lo que haya en buffer del puerto serie
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte) 0x54; //T
                packet[1] = (byte)Convert.ToByte(Convert.ToChar(Convert.ToInt32(textBox1.Text)));
                packet[2] = (byte) 0xFF;
                packet[3] = (byte) 0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x74;
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] packet = new byte[4];

            while (serialPort1.BytesToRead >= 4)
            {
                serialPort1.Read(packet, 0, 4);

                if (packet[0] == 0x30)
                {
                    temperatura = (double)(packet[1] + packet[2] / 100.0);
                }
                if (packet[0] == 0x40)
                {
                    velocidad= (double)(packet[1] + packet[2]/100.0);
                }
                if (packet[0] == 0x20)
                {
                    posicion = (double)(packet[1]);
                }
                if (packet[0] == 0x21)
                {
                    posicion_remota = (double)(packet[1]);
                }
                if (packet[0] == 0x31)
                {
                    temperatura_remota = (double)(packet[1] + packet[2] / 100.0);
                }
                if (packet[0] == 0x41)
                {
                    velocidad_remota = (double)(packet[1] + packet[2] / 100.0);
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            string cadena;
                       
            cadena = Convert.ToString(temperatura);
            cadena = cadena + "ºC";
            //textBox1.Text = cadena;                     //TEMPERATURA
            lbDigitalMeter1.Value = temperatura;        //TEMPERATURA
            lbDigitalMeter2.Value = temperatura_remota;

            lbAnalogMeter1.Value = velocidad;           //VELOCIDAD PASO A PASO
            lbAnalogMeter2.Value = velocidad_remota;


            cadena = Convert.ToString(posicion); 
            cadena = cadena + "º";
            textBox2.Text = cadena;                    //SERVOMOTOR

            cadena = Convert.ToString(posicion_remota);
            cadena = cadena + "º";
            textBox7.Text = cadena;

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void lbDigitalMeter1_Load(object sender, EventArgs e)
        {

        }

        private void lbAnalogMeter1_Load(object sender, EventArgs e)
        {

        }

        private void lbKnob1_Load(object sender, EventArgs e)
        {

        }

        private void lbKnob1_KnobChangeValue(object sender, LBSoft.IndustrialCtrls.Knobs.LBKnobEventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x4D; //M
                packet[1] = Convert.ToByte(lbKnob1.Value);
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }

        }

        private void lbKnob2_KnobChangeValue(object sender, LBSoft.IndustrialCtrls.Knobs.LBKnobEventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x53; //S
                packet[1] = Convert.ToByte(lbKnob2.Value);
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x49;//I
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x44;//D
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x50;  //P
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x41; //A
                packet[1] = (byte)Convert.ToByte(Convert.ToChar(Convert.ToInt32(textBoxEspera.Text)));
                packet[2] = (byte)Convert.ToByte(Convert.ToChar(Convert.ToInt32(textBoxVelocidad.Text)));
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void lbAnalogMeter2_Load(object sender, EventArgs e)
        {

        }

        private void button8_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x58; //X
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }

        }

        private void button9_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x43; //C
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x52; //R
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }
    }
}
