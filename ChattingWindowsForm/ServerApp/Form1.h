#pragma once

namespace ServerApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace FormatterText;
	using namespace System::Collections::Generic;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  txtIPAddress;
	private: System::Windows::Forms::Button^  btnListen;
	private: System::Windows::Forms::RichTextBox^  rtbMain;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtIPAddress = (gcnew System::Windows::Forms::TextBox());
			this->btnListen = (gcnew System::Windows::Forms::Button());
			this->rtbMain = (gcnew System::Windows::Forms::RichTextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(54, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"IpAddress";
			// 
			// txtIPAddress
			// 
			this->txtIPAddress->Location = System::Drawing::Point(74, 13);
			this->txtIPAddress->Name = L"txtIPAddress";
			this->txtIPAddress->Size = System::Drawing::Size(219, 20);
			this->txtIPAddress->TabIndex = 1;
			// 
			// btnListen
			// 
			this->btnListen->Location = System::Drawing::Point(317, 13);
			this->btnListen->Name = L"btnListen";
			this->btnListen->Size = System::Drawing::Size(75, 23);
			this->btnListen->TabIndex = 2;
			this->btnListen->Text = L"Listen";
			this->btnListen->UseVisualStyleBackColor = true;
			this->btnListen->Click += gcnew System::EventHandler(this, &Form1::btnListen_Click);
			// 
			// rtbMain
			// 
			this->rtbMain->Location = System::Drawing::Point(16, 70);
			this->rtbMain->Name = L"rtbMain";
			this->rtbMain->Size = System::Drawing::Size(376, 213);
			this->rtbMain->TabIndex = 3;
			this->rtbMain->Text = L"";
			this->rtbMain->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::rtbMain_KeyPress);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(412, 383);
			this->Controls->Add(this->rtbMain);
			this->Controls->Add(this->btnListen);
			this->Controls->Add(this->txtIPAddress);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void rtbMain_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				e->Handled=true;
			 };
			 //Init server and list Client
	public: static Socket^ server;
	public: static List<Socket^>^ lstClient = gcnew List<Socket^>();
	public: static IPEndPoint^ ipe;
	public: static Thread^ xulyClient;
	private: System::Void btnListen_Click(System::Object^  sender, System::EventArgs^  e) {
				 ipe = gcnew IPEndPoint(IPAdrress::Parse(txtIPAddress->Text), 2008);
				 backgroundWorker1->WorkerSupportsCancellation = true;
				 backgroundWorker1->RunWorkerAsync();

			 }
			 static void LangNgheClient(Object^ obj)
			 {
				 Socket^ sk = (Socket^)obj;
				 while (true)
				 {
					 try
					 {
						 array<unsigned char> buff gcnew array<unsigned char> (1024);
						 int recv.Receive(buff);

						 //Rec msg
						 for each(Socket^ sock in lstClient)
						 {
							 try
							 {
								 sock->Send(buff, buff.Length, SocketFlags::None);
							 }
							 catch (Exception* ex)
							 {

							 }
						 }
					 }
					 catch (Exception* ex)
					 {
					 	lstClient->Remove(sk);
						return;
					 }

				 }
			 }
			 void AddTextToRichTextBox(String^ text, System::Drawing::Font^ font, System::Drawing::Color^ color)
			 {
				rtbMain->SelectionFont = font;
				rtbMain->SelectionColor = (Color) color;
				rtbMain->AppendText(text + "\n");
			 }
			 
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 server = gcnew Socket (AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);

			 }
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 server->Bind(ipe);
			 server->Listen(10);
			 String^ text = "Server is listening...";
			 System::Drawing::Font^ ft = gcnew System::Drawing::Font("Arial", 15, FontStyle::Bold);
			 System::Drawing::Color^ cl = Color::Red;
			 AddTextToRichTextBox(text, )
			 while(true)
			 {
				 Socket^ clientAccept = server->Accept();
				 //Add list 
				 lstClient->Add(clientAccept);
				 
				 //Create Thread
				 xulyClient = gcnew Thread(gcnew ParameterizedThreadStart(Server::Form1::LangNgheClient));
				 xulyClient->IsBackground = true;
				 xulyClient->Start(clientAccept);

				 //Thongbao
				 String^ textThongBao = L"Chap nhan ket noi " + clientAccept->RemoteEndPoint.ToString();
				 System::Drawing::Font^ ftTB = gcnew System::Drawing::Font("Time New Roman", 10, FontStyle::Bold);
				 System::Drawing::Color^ clTB = Color::Green;
				AddTextToRichTextBox(textThongBao, ftTB, clTB);

			 }
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 if (backgroundWorker1->IsBusy)
			 {
				 backgroundWorker1->CancelAsync();

			 }
		 }
};
}

