#pragma once

#include "aes2.h"

namespace AesGui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
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
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonBrowseInput;
	private: System::Windows::Forms::TextBox^  textBoxInput;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  buttonBrowseOutput;
	private: System::Windows::Forms::TextBox^  textBoxOutput;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonLoadKey;
	private: System::Windows::Forms::Button^  buttonCreateKey;
	private: System::Windows::Forms::TextBox^  textBoxKey;


	private: System::Windows::Forms::Button^  buttonDecrypt;
	private: System::Windows::Forms::Button^  buttonEncrypt;
	protected:

	protected:

	protected:

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
			this->buttonBrowseInput = (gcnew System::Windows::Forms::Button());
			this->textBoxInput = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonDecrypt = (gcnew System::Windows::Forms::Button());
			this->buttonEncrypt = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonBrowseOutput = (gcnew System::Windows::Forms::Button());
			this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonLoadKey = (gcnew System::Windows::Forms::Button());
			this->buttonCreateKey = (gcnew System::Windows::Forms::Button());
			this->textBoxKey = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// buttonBrowseInput
			// 
			this->buttonBrowseInput->Location = System::Drawing::Point(337, 34);
			this->buttonBrowseInput->Name = L"buttonBrowseInput";
			this->buttonBrowseInput->Size = System::Drawing::Size(75, 23);
			this->buttonBrowseInput->TabIndex = 0;
			this->buttonBrowseInput->Text = L"Browse";
			this->buttonBrowseInput->UseVisualStyleBackColor = true;
			this->buttonBrowseInput->Click += gcnew System::EventHandler(this, &Main::buttonBrowseInput_Click);
			// 
			// textBoxInput
			// 
			this->textBoxInput->Location = System::Drawing::Point(13, 36);
			this->textBoxInput->Name = L"textBoxInput";
			this->textBoxInput->Size = System::Drawing::Size(309, 20);
			this->textBoxInput->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->buttonDecrypt);
			this->groupBox1->Controls->Add(this->buttonEncrypt);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->buttonBrowseOutput);
			this->groupBox1->Controls->Add(this->textBoxOutput);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->buttonBrowseInput);
			this->groupBox1->Controls->Add(this->textBoxInput);
			this->groupBox1->Location = System::Drawing::Point(12, 147);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(426, 162);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Cryptography";
			// 
			// buttonDecrypt
			// 
			this->buttonDecrypt->Enabled = false;
			this->buttonDecrypt->Location = System::Drawing::Point(105, 121);
			this->buttonDecrypt->Name = L"buttonDecrypt";
			this->buttonDecrypt->Size = System::Drawing::Size(75, 23);
			this->buttonDecrypt->TabIndex = 5;
			this->buttonDecrypt->Text = L"Decrypt";
			this->buttonDecrypt->UseVisualStyleBackColor = true;
			this->buttonDecrypt->Click += gcnew System::EventHandler(this, &Main::buttonDecrypt_Click);
			// 
			// buttonEncrypt
			// 
			this->buttonEncrypt->Enabled = false;
			this->buttonEncrypt->Location = System::Drawing::Point(13, 121);
			this->buttonEncrypt->Name = L"buttonEncrypt";
			this->buttonEncrypt->Size = System::Drawing::Size(75, 23);
			this->buttonEncrypt->TabIndex = 4;
			this->buttonEncrypt->Text = L"Encrypt";
			this->buttonEncrypt->UseVisualStyleBackColor = true;
			this->buttonEncrypt->Click += gcnew System::EventHandler(this, &Main::buttonEncrypt_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 67);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(39, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Output";
			// 
			// buttonBrowseOutput
			// 
			this->buttonBrowseOutput->Location = System::Drawing::Point(337, 81);
			this->buttonBrowseOutput->Name = L"buttonBrowseOutput";
			this->buttonBrowseOutput->Size = System::Drawing::Size(75, 23);
			this->buttonBrowseOutput->TabIndex = 3;
			this->buttonBrowseOutput->Text = L"Browse";
			this->buttonBrowseOutput->UseVisualStyleBackColor = true;
			this->buttonBrowseOutput->Click += gcnew System::EventHandler(this, &Main::buttonBrowseOutput_Click);
			// 
			// textBoxOutput
			// 
			this->textBoxOutput->Location = System::Drawing::Point(13, 83);
			this->textBoxOutput->Name = L"textBoxOutput";
			this->textBoxOutput->Size = System::Drawing::Size(309, 20);
			this->textBoxOutput->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Input";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->buttonLoadKey);
			this->groupBox2->Controls->Add(this->buttonCreateKey);
			this->groupBox2->Controls->Add(this->textBoxKey);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(12, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(426, 118);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Key Management";
			// 
			// buttonLoadKey
			// 
			this->buttonLoadKey->Location = System::Drawing::Point(105, 78);
			this->buttonLoadKey->Name = L"buttonLoadKey";
			this->buttonLoadKey->Size = System::Drawing::Size(75, 23);
			this->buttonLoadKey->TabIndex = 3;
			this->buttonLoadKey->Text = L"Load";
			this->buttonLoadKey->UseVisualStyleBackColor = true;
			this->buttonLoadKey->Click += gcnew System::EventHandler(this, &Main::buttonLoadKey_Click);
			// 
			// buttonCreateKey
			// 
			this->buttonCreateKey->Location = System::Drawing::Point(13, 78);
			this->buttonCreateKey->Name = L"buttonCreateKey";
			this->buttonCreateKey->Size = System::Drawing::Size(75, 23);
			this->buttonCreateKey->TabIndex = 2;
			this->buttonCreateKey->Text = L"Create";
			this->buttonCreateKey->UseVisualStyleBackColor = true;
			this->buttonCreateKey->Click += gcnew System::EventHandler(this, &Main::buttonCreateKey_Click);
			// 
			// textBoxKey
			// 
			this->textBoxKey->Location = System::Drawing::Point(13, 43);
			this->textBoxKey->Name = L"textBoxKey";
			this->textBoxKey->Size = System::Drawing::Size(399, 20);
			this->textBoxKey->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(10, 20);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(25, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Key";
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(450, 323);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Main";
			this->Text = L"AesLib";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		std::string managedStrToNative(System::String^ sysstr)
		{
			using System::IntPtr;
			using System::Runtime::InteropServices::Marshal;

			IntPtr ip = Marshal::StringToHGlobalAnsi(sysstr);
			std::string outString = static_cast<const char*>(ip.ToPointer());
			Marshal::FreeHGlobal(ip);
			return outString;
		}

		String^ key;
		bool key_loaded = false;
	private: System::Void buttonLoadKey_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ ofd = gcnew OpenFileDialog();
				 ofd->Filter = "All Files|*.*";
				 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 unsigned char buffer[16] = { 0x00 };
				 string fname = managedStrToNative(ofd->FileName);
				 key = ofd->FileName;
				 Aes::LoadKey(fname, 128, buffer);
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
	private: System::Void buttonBrowseInput_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ ofd = gcnew OpenFileDialog();
				 ofd->Filter = "All Files|*.*";
				 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 this->textBoxInput->Text = ofd->FileName;
	}
	private: System::Void buttonBrowseOutput_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveFileDialog^ sfd = gcnew SaveFileDialog();
				 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 this->textBoxOutput->Text = sfd->FileName;
	}
	private: System::Void buttonCreateKey_Click(System::Object^  sender, System::EventArgs^  e) {
				 SaveFileDialog^ sfd = gcnew SaveFileDialog();
				 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 string fname = managedStrToNative(sfd->FileName);
				 key = sfd->FileName;
				 Aes::CreateKey(fname, 128);

				 unsigned char buffer[16] = { 0x00 };
				 Aes::LoadKey(fname, 128, buffer);
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
	private: System::Void buttonEncrypt_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ input = this->textBoxInput->Text;
				 String^ output = this->textBoxOutput->Text;
				 if (input == "" || output == "")
				 {
					 MessageBox::Show("Select an input and output file");
					 return;
				 }
				 Aes128 aes;

				 string key_str = managedStrToNative(key);
				 string in = managedStrToNative(input);
				 string out = managedStrToNative(output);
				 aes.EncryptFileCbc2(in, out, key_str);
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
				 Aes128 aes;

				 string key_str = managedStrToNative(key);
				 string in = managedStrToNative(input);
				 string out = managedStrToNative(output);
				 aes.DecryptFileCbc2(in, out, key_str);
				 MessageBox::Show("File decrypted");
	}
	};
}
