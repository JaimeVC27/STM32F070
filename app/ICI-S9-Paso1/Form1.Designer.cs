namespace ICI_S9_Paso1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.button1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lbDigitalMeter1 = new LBSoft.IndustrialCtrls.Meters.LBDigitalMeter();
            this.lbAnalogMeter1 = new LBSoft.IndustrialCtrls.Meters.LBAnalogMeter();
            this.lbKnob1 = new LBSoft.IndustrialCtrls.Knobs.LBKnob();
            this.lbKnob2 = new LBSoft.IndustrialCtrls.Knobs.LBKnob();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxEspera = new System.Windows.Forms.TextBox();
            this.textBoxVelocidad = new System.Windows.Forms.TextBox();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.lbAnalogMeter2 = new LBSoft.IndustrialCtrls.Meters.LBAnalogMeter();
            this.lbDigitalMeter2 = new LBSoft.IndustrialCtrls.Meters.LBDigitalMeter();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 161);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(231, 38);
            this.button1.TabIndex = 0;
            this.button1.Text = "Tiempo de lectura";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 38400;
            this.serialPort1.PortName = "COM7";
            this.serialPort1.ReceivedBytesThreshold = 4;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox1.Font = new System.Drawing.Font("Courier New", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(13, 203);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(231, 45);
            this.textBox1.TabIndex = 2;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lbDigitalMeter1
            // 
            this.lbDigitalMeter1.BackColor = System.Drawing.Color.Transparent;
            this.lbDigitalMeter1.ForeColor = System.Drawing.SystemColors.InfoText;
            this.lbDigitalMeter1.Format = "00.00";
            this.lbDigitalMeter1.Location = new System.Drawing.Point(13, 71);
            this.lbDigitalMeter1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lbDigitalMeter1.Name = "lbDigitalMeter1";
            this.lbDigitalMeter1.Renderer = null;
            this.lbDigitalMeter1.Signed = false;
            this.lbDigitalMeter1.Size = new System.Drawing.Size(233, 69);
            this.lbDigitalMeter1.TabIndex = 3;
            this.lbDigitalMeter1.Value = 0D;
            this.lbDigitalMeter1.Load += new System.EventHandler(this.lbDigitalMeter1_Load);
            // 
            // lbAnalogMeter1
            // 
            this.lbAnalogMeter1.BackColor = System.Drawing.Color.Transparent;
            this.lbAnalogMeter1.BodyColor = System.Drawing.Color.Indigo;
            this.lbAnalogMeter1.Location = new System.Drawing.Point(269, 70);
            this.lbAnalogMeter1.MaxValue = 15D;
            this.lbAnalogMeter1.MeterStyle = LBSoft.IndustrialCtrls.Meters.LBAnalogMeter.AnalogMeterStyle.Circular;
            this.lbAnalogMeter1.MinValue = 0D;
            this.lbAnalogMeter1.Name = "lbAnalogMeter1";
            this.lbAnalogMeter1.NeedleColor = System.Drawing.Color.Yellow;
            this.lbAnalogMeter1.Renderer = null;
            this.lbAnalogMeter1.ScaleColor = System.Drawing.Color.White;
            this.lbAnalogMeter1.ScaleDivisions = 10;
            this.lbAnalogMeter1.ScaleSubDivisions = 10;
            this.lbAnalogMeter1.Size = new System.Drawing.Size(263, 245);
            this.lbAnalogMeter1.TabIndex = 4;
            this.lbAnalogMeter1.Value = 0D;
            this.lbAnalogMeter1.ViewGlass = false;
            this.lbAnalogMeter1.Load += new System.EventHandler(this.lbAnalogMeter1_Load);
            // 
            // lbKnob1
            // 
            this.lbKnob1.BackColor = System.Drawing.Color.Transparent;
            this.lbKnob1.DrawRatio = 0.325F;
            this.lbKnob1.IndicatorColor = System.Drawing.Color.Red;
            this.lbKnob1.IndicatorOffset = 10F;
            this.lbKnob1.KnobCenter = ((System.Drawing.PointF)(resources.GetObject("lbKnob1.KnobCenter")));
            this.lbKnob1.KnobColor = System.Drawing.Color.Gray;
            this.lbKnob1.KnobRect = ((System.Drawing.RectangleF)(resources.GetObject("lbKnob1.KnobRect")));
            this.lbKnob1.Location = new System.Drawing.Point(463, 298);
            this.lbKnob1.MaxValue = 13.5F;
            this.lbKnob1.MinValue = 1F;
            this.lbKnob1.Name = "lbKnob1";
            this.lbKnob1.Renderer = null;
            this.lbKnob1.ScaleColor = System.Drawing.Color.Black;
            this.lbKnob1.Size = new System.Drawing.Size(69, 65);
            this.lbKnob1.StepValue = 0.1F;
            this.lbKnob1.Style = LBSoft.IndustrialCtrls.Knobs.LBKnob.KnobStyle.Circular;
            this.lbKnob1.TabIndex = 5;
            this.lbKnob1.Value = 0F;
            this.lbKnob1.KnobChangeValue += new LBSoft.IndustrialCtrls.Knobs.KnobChangeValue(this.lbKnob1_KnobChangeValue);
            this.lbKnob1.Load += new System.EventHandler(this.lbKnob1_Load);
            // 
            // lbKnob2
            // 
            this.lbKnob2.BackColor = System.Drawing.Color.Transparent;
            this.lbKnob2.DrawRatio = 0.81F;
            this.lbKnob2.IndicatorColor = System.Drawing.Color.Black;
            this.lbKnob2.IndicatorOffset = 10F;
            this.lbKnob2.KnobCenter = ((System.Drawing.PointF)(resources.GetObject("lbKnob2.KnobCenter")));
            this.lbKnob2.KnobColor = System.Drawing.Color.DarkOrange;
            this.lbKnob2.KnobRect = ((System.Drawing.RectangleF)(resources.GetObject("lbKnob2.KnobRect")));
            this.lbKnob2.Location = new System.Drawing.Point(13, 319);
            this.lbKnob2.MaxValue = 90F;
            this.lbKnob2.MinValue = 0F;
            this.lbKnob2.Name = "lbKnob2";
            this.lbKnob2.Renderer = null;
            this.lbKnob2.ScaleColor = System.Drawing.Color.DimGray;
            this.lbKnob2.Size = new System.Drawing.Size(164, 162);
            this.lbKnob2.StepValue = 1F;
            this.lbKnob2.Style = LBSoft.IndustrialCtrls.Knobs.LBKnob.KnobStyle.Circular;
            this.lbKnob2.TabIndex = 6;
            this.lbKnob2.Value = 0F;
            this.lbKnob2.KnobChangeValue += new LBSoft.IndustrialCtrls.Knobs.KnobChangeValue(this.lbKnob2_KnobChangeValue);
            // 
            // textBox2
            // 
            this.textBox2.Enabled = false;
            this.textBox2.Font = new System.Drawing.Font("Courier New", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.Location = new System.Drawing.Point(12, 500);
            this.textBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(190, 45);
            this.textBox2.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(8, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(169, 25);
            this.label1.TabIndex = 8;
            this.label1.Text = "Temperatura local";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(10, 290);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(195, 25);
            this.label2.TabIndex = 9;
            this.label2.Text = "Posición Servo Local";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(269, 430);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(263, 38);
            this.button3.TabIndex = 10;
            this.button3.Text = "Activar control por potenciometro";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(269, 472);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(263, 38);
            this.button4.TabIndex = 11;
            this.button4.Text = "Apertura y cierre";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(266, 513);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(123, 17);
            this.label3.TabIndex = 12;
            this.label3.Text = "Tiempo de espera";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(409, 513);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 17);
            this.label4.TabIndex = 13;
            this.label4.Text = "Velocidad";
            // 
            // textBoxEspera
            // 
            this.textBoxEspera.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxEspera.Location = new System.Drawing.Point(269, 536);
            this.textBoxEspera.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxEspera.Name = "textBoxEspera";
            this.textBoxEspera.Size = new System.Drawing.Size(120, 30);
            this.textBoxEspera.TabIndex = 14;
            this.textBoxEspera.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // textBoxVelocidad
            // 
            this.textBoxVelocidad.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBoxVelocidad.Location = new System.Drawing.Point(412, 536);
            this.textBoxVelocidad.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxVelocidad.Name = "textBoxVelocidad";
            this.textBoxVelocidad.Size = new System.Drawing.Size(120, 30);
            this.textBoxVelocidad.TabIndex = 15;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(269, 367);
            this.button5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(120, 38);
            this.button5.TabIndex = 16;
            this.button5.Text = "Izquierda";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(412, 367);
            this.button6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(120, 38);
            this.button6.TabIndex = 17;
            this.button6.Text = "Derecha";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button7
            // 
            this.button7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button7.Location = new System.Drawing.Point(595, 10);
            this.button7.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(496, 38);
            this.button7.TabIndex = 18;
            this.button7.Text = "Monitorizar placa remota";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(604, 224);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(215, 25);
            this.label7.TabIndex = 28;
            this.label7.Text = "Posición Servo Remoto";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(590, 70);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(189, 25);
            this.label8.TabIndex = 27;
            this.label8.Text = "Temperatura remota";
            // 
            // textBox7
            // 
            this.textBox7.Enabled = false;
            this.textBox7.Font = new System.Drawing.Font("Courier New", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox7.Location = new System.Drawing.Point(607, 253);
            this.textBox7.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(150, 45);
            this.textBox7.TabIndex = 26;
            // 
            // lbAnalogMeter2
            // 
            this.lbAnalogMeter2.BackColor = System.Drawing.Color.Transparent;
            this.lbAnalogMeter2.BodyColor = System.Drawing.Color.Crimson;
            this.lbAnalogMeter2.Location = new System.Drawing.Point(835, 110);
            this.lbAnalogMeter2.MaxValue = 15D;
            this.lbAnalogMeter2.MeterStyle = LBSoft.IndustrialCtrls.Meters.LBAnalogMeter.AnalogMeterStyle.Circular;
            this.lbAnalogMeter2.MinValue = 0D;
            this.lbAnalogMeter2.Name = "lbAnalogMeter2";
            this.lbAnalogMeter2.NeedleColor = System.Drawing.Color.Yellow;
            this.lbAnalogMeter2.Renderer = null;
            this.lbAnalogMeter2.ScaleColor = System.Drawing.Color.White;
            this.lbAnalogMeter2.ScaleDivisions = 10;
            this.lbAnalogMeter2.ScaleSubDivisions = 10;
            this.lbAnalogMeter2.Size = new System.Drawing.Size(263, 245);
            this.lbAnalogMeter2.TabIndex = 23;
            this.lbAnalogMeter2.Value = 0D;
            this.lbAnalogMeter2.ViewGlass = false;
            this.lbAnalogMeter2.Load += new System.EventHandler(this.lbAnalogMeter2_Load);
            // 
            // lbDigitalMeter2
            // 
            this.lbDigitalMeter2.BackColor = System.Drawing.Color.Transparent;
            this.lbDigitalMeter2.ForeColor = System.Drawing.SystemColors.InfoText;
            this.lbDigitalMeter2.Format = "00.00";
            this.lbDigitalMeter2.Location = new System.Drawing.Point(595, 91);
            this.lbDigitalMeter2.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lbDigitalMeter2.Name = "lbDigitalMeter2";
            this.lbDigitalMeter2.Renderer = null;
            this.lbDigitalMeter2.Signed = false;
            this.lbDigitalMeter2.Size = new System.Drawing.Size(233, 69);
            this.lbDigitalMeter2.TabIndex = 22;
            this.lbDigitalMeter2.Value = 0D;
            // 
            // button8
            // 
            this.button8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button8.Location = new System.Drawing.Point(595, 442);
            this.button8.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(496, 38);
            this.button8.TabIndex = 29;
            this.button8.Text = "Mostrar en el Display";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // button9
            // 
            this.button9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button9.Location = new System.Drawing.Point(595, 484);
            this.button9.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(496, 74);
            this.button9.TabIndex = 30;
            this.button9.Text = "Cancelar todos los comandos";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(264, 23);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(206, 25);
            this.label5.TabIndex = 31;
            this.label5.Text = "Velocidad Motor Local";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(844, 70);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(226, 25);
            this.label6.TabIndex = 32;
            this.label6.Text = "Velocidad Motor Remota";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1103, 572);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.textBox7);
            this.Controls.Add(this.lbAnalogMeter2);
            this.Controls.Add(this.lbDigitalMeter2);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.textBoxVelocidad);
            this.Controls.Add(this.textBoxEspera);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.lbKnob2);
            this.Controls.Add(this.lbKnob1);
            this.Controls.Add(this.lbAnalogMeter1);
            this.Controls.Add(this.lbDigitalMeter1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "ICI-S9-Paso1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Timer timer1;
        private LBSoft.IndustrialCtrls.Meters.LBDigitalMeter lbDigitalMeter1;
        private LBSoft.IndustrialCtrls.Meters.LBAnalogMeter lbAnalogMeter1;
        private LBSoft.IndustrialCtrls.Knobs.LBKnob lbKnob1;
        private LBSoft.IndustrialCtrls.Knobs.LBKnob lbKnob2;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxEspera;
        private System.Windows.Forms.TextBox textBoxVelocidad;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox7;
        private LBSoft.IndustrialCtrls.Meters.LBAnalogMeter lbAnalogMeter2;
        private LBSoft.IndustrialCtrls.Meters.LBDigitalMeter lbDigitalMeter2;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}

