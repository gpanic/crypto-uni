#pragma once
#include <string>
#include "rc4.h"
using namespace std;

namespace Gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  buttonLoad;
	private: System::Windows::Forms::Button^  buttonCreate;


	private: System::Windows::Forms::TextBox^  textBoxKey;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  buttonDecrypt;
	private: System::Windows::Forms::Button^  buttonEncrypt;
	private: System::Windows::Forms::TextBox^  textBoxOutput;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxInput;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  buttonOutput;
	private: System::Windows::Forms::Button^  buttonInput;
	protected:

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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonLoad = (gcnew System::Windows::Forms::Button());
			this->buttonCreate = (gcnew System::Windows::Forms::Button());
			this->textBoxKey = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonOutput = (gcnew System::Windows::Forms::Button());
			this->buttonInput = (gcnew System::Windows::Forms::Button());
			this->buttonDecrypt = (gcnew System::Windows::Forms::Button());
			this->buttonEncrypt = (gcnew System::Windows::Forms::Button());
			this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxInput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->buttonLoad);
			this->groupBox1->Controls->Add(this->buttonCreate);
			this->groupBox1->Controls->Add(this->textBoxKey);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(347, 79);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Key";
			// 
			// buttonLoad
			// 
			this->buttonLoad->Location = System::Drawing::Point(6, 45);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(75, 23);
			this->buttonLoad->TabIndex = 2;
			this->buttonLoad->Text = L"Load";
			this->buttonLoad->UseVisualStyleBackColor = true;
			this->buttonLoad->Click += gcnew System::EventHandler(this, &MainWindow::buttonLoad_Click);
			// 
			// buttonCreate
			// 
			this->buttonCreate->Location = System::Drawing::Point(87, 45);
			this->buttonCreate->Name = L"buttonCreate";
			this->buttonCreate->Size = System::Drawing::Size(75, 23);
			this->buttonCreate->TabIndex = 1;
			this->buttonCreate->Text = L"Create";
			this->buttonCreate->UseVisualStyleBackColor = true;
			this->buttonCreate->Click += gcnew System::EventHandler(this, &MainWindow::buttonCreate_Click);
			// 
			// textBoxKey
			// 
			this->textBoxKey->Location = System::Drawing::Point(6, 19);
			this->textBoxKey->Name = L"textBoxKey";
			this->textBoxKey->Size = System::Drawing::Size(335, 20);
			this->textBoxKey->TabIndex = 0;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->buttonOutput);
			this->groupBox2->Controls->Add(this->buttonInput);
			this->groupBox2->Controls->Add(this->buttonDecrypt);
			this->groupBox2->Controls->Add(this->buttonEncrypt);
			this->groupBox2->Controls->Add(this->textBoxOutput);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->textBoxInput);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(12, 98);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(347, 151);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Encryption/Decryption";
			// 
			// buttonOutput
			// 
			this->buttonOutput->Location = System::Drawing::Point(266, 78);
			this->buttonOutput->Name = L"buttonOutput";
			this->buttonOutput->Size = System::Drawing::Size(75, 23);
			this->buttonOutput->TabIndex = 7;
			this->buttonOutput->Text = L"Browse";
			this->buttonOutput->UseVisualStyleBackColor = true;
			this->buttonOutput->Click += gcnew System::EventHandler(this, &MainWindow::buttonOutput_Click);
			// 
			// buttonInput
			// 
			this->buttonInput->Location = System::Drawing::Point(266, 35);
			this->buttonInput->Name = L"buttonInput";
			this->buttonInput->Size = System::Drawing::Size(75, 23);
			this->buttonInput->TabIndex = 6;
			this->buttonInput->Text = L"Browse";
			this->buttonInput->UseVisualStyleBackColor = true;
			this->buttonInput->Click += gcnew System::EventHandler(this, &MainWindow::buttonInput_Click);
			// 
			// buttonDecrypt
			// 
			this->buttonDecrypt->Enabled = false;
			this->buttonDecrypt->Location = System::Drawing::Point(90, 111);
			this->buttonDecrypt->Name = L"buttonDecrypt";
			this->buttonDecrypt->Size = System::Drawing::Size(75, 23);
			this->buttonDecrypt->TabIndex = 5;
			this->buttonDecrypt->Text = L"Decrypt";
			this->buttonDecrypt->UseVisualStyleBackColor = true;
			this->buttonDecrypt->Click += gcnew System::EventHandler(this, &MainWindow::buttonDecrypt_Click);
			// 
			// buttonEncrypt
			// 
			this->buttonEncrypt->Enabled = false;
			this->buttonEncrypt->Location = System::Drawing::Point(9, 111);
			this->buttonEncrypt->Name = L"buttonEncrypt";
			this->buttonEncrypt->Size = System::Drawing::Size(75, 23);
			this->buttonEncrypt->TabIndex = 4;
			this->buttonEncrypt->Text = L"Encrypt";
			this->buttonEncrypt->UseVisualStyleBackColor = true;
			this->buttonEncrypt->Click += gcnew System::EventHandler(this, &MainWindow::buttonEncrypt_Click);
			// 
			// textBoxOutput
			// 
			this->textBoxOutput->Location = System::Drawing::Point(9, 80);
			this->textBoxOutput->Name = L"textBoxOutput";
			this->textBoxOutput->Size = System::Drawing::Size(251, 20);
			this->textBoxOutput->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 63);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(39, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Output";
			// 
			// textBoxInput
			// 
			this->textBoxInput->Location = System::Drawing::Point(10, 37);
			this->textBoxInput->Name = L"textBoxInput";
			this->textBoxInput->Size = System::Drawing::Size(250, 20);
			this->textBoxInput->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Input";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(371, 261);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		string managedStrToNative(System::String^ sysstr)
		{
			using System::IntPtr;
			using System::Runtime::InteropServices::Marshal;

			IntPtr ip = Marshal::StringToHGlobalAnsi(sysstr);
			std::string outString = static_cast<const char*>(ip.ToPointer());
			Marshal::FreeHGlobal(ip);
			return outString;
		}

		bool key_loaded = false;
		String^ key;
	private: System::Void buttonLoad_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ ofd = gcnew OpenFileDialog();
				 ofd->Filter = "All Files|*.*";
				 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 unsigned char buffer[16] = { 0x00 };
				 string fname = managedStrToNative(ofd->FileName);
				 key = ofd->FileName;
				 Rc4::load_key(fname, buffer);
				 key_loaded = true;
				 this->buttonEncrypt->Enabled = true;
				 this->buttonDecrypt->Enabled = true;

				 System::Text::StringBuilder sb;
				 for (int i = 0; i < 16; ++i)
				 {
					 sb.AppendFormat("{0:X2} ", buffer[i]);
				 }
				 this->textBoxKey->Text = sb.ToString();
	}
	private: System::Void buttonCreate_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveFileDialog^ sfd = gcnew SaveFileDialog();
				 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 string fname = managedStrToNative(sfd->FileName);
				 key = sfd->FileName;
				 Rc4::create_key(fname);

				 unsigned char buffer[16] = { 0x00 };
				 Rc4::load_key(fname, buffer);
				 key_loaded = true;
				 this->buttonEncrypt->Enabled = true;
				 this->buttonDecrypt->Enabled = true;

				 System::Text::StringBuilder sb;
				 for (int i = 0; i < 16; ++i)
				 {
					 sb.AppendFormat("{0:X2} ", buffer[i]);
				 }
				 this->textBoxKey->Text = sb.ToString();

				 MessageBox::Show("Key created and loaded");
	}
	private: System::Void buttonInput_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ ofd = gcnew OpenFileDialog();
				 ofd->Filter = "All Files|*.*";
				 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 this->textBoxInput->Text = ofd->FileName;
	}
	private: System::Void buttonOutput_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveFileDialog^ sfd = gcnew SaveFileDialog();
				 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 this->textBoxOutput->Text = sfd->FileName;
	}
	private: System::Void buttonEncrypt_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ input = this->textBoxInput->Text;
				 String^ output = this->textBoxOutput->Text;
				 if (input == "" || output == "")
				 {
					 MessageBox::Show("Select an input and output file");
					 return;
				 }

				 string key_str = managedStrToNative(key);
				 string in = managedStrToNative(input);
				 string out = managedStrToNative(output);
				 Rc4::encrypt_file2(in, out, key_str);
				 MessageBox::Show("File encrypted");
	}
	private: System::Void buttonDecrypt_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ input = this->textBoxInput->Text;
				 String^ output = this->textBoxOutput->Text;
				 if (input == "" || output == "")
				 {
					 MessageBox::Show("Select an input and output file");
					 return;
				 }
				 string key_str = managedStrToNative(key);
				 string in = managedStrToNative(input);
				 string out = managedStrToNative(output);
				 Rc4::encrypt_file2(in, out, key_str);
				 MessageBox::Show("File decrypted");
	}
	};
}
