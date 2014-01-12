#pragma once

#include "sha256.h"
#include <msclr\marshal_cppstd.h>

namespace Sha256Gui {

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
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  textBoxFile;
	private: System::Windows::Forms::Button^  buttonFile;
	private: System::Windows::Forms::Button^  buttonHash;
	private: System::Windows::Forms::TextBox^  textBoxHash;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  buttonVerify;

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
			this->textBoxFile = (gcnew System::Windows::Forms::TextBox());
			this->buttonFile = (gcnew System::Windows::Forms::Button());
			this->buttonHash = (gcnew System::Windows::Forms::Button());
			this->textBoxHash = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonVerify = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(23, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"File";
			// 
			// textBoxFile
			// 
			this->textBoxFile->Location = System::Drawing::Point(12, 25);
			this->textBoxFile->Name = L"textBoxFile";
			this->textBoxFile->Size = System::Drawing::Size(365, 20);
			this->textBoxFile->TabIndex = 1;
			// 
			// buttonFile
			// 
			this->buttonFile->Location = System::Drawing::Point(383, 22);
			this->buttonFile->Name = L"buttonFile";
			this->buttonFile->Size = System::Drawing::Size(75, 23);
			this->buttonFile->TabIndex = 2;
			this->buttonFile->Text = L"Browse";
			this->buttonFile->UseVisualStyleBackColor = true;
			this->buttonFile->Click += gcnew System::EventHandler(this, &Main::buttonFile_Click);
			// 
			// buttonHash
			// 
			this->buttonHash->Location = System::Drawing::Point(12, 112);
			this->buttonHash->Name = L"buttonHash";
			this->buttonHash->Size = System::Drawing::Size(75, 23);
			this->buttonHash->TabIndex = 3;
			this->buttonHash->Text = L"Hash";
			this->buttonHash->UseVisualStyleBackColor = true;
			this->buttonHash->Click += gcnew System::EventHandler(this, &Main::buttonHash_Click);
			// 
			// textBoxHash
			// 
			this->textBoxHash->Location = System::Drawing::Point(12, 70);
			this->textBoxHash->Name = L"textBoxHash";
			this->textBoxHash->Size = System::Drawing::Size(446, 20);
			this->textBoxHash->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Hash";
			// 
			// buttonVerify
			// 
			this->buttonVerify->Location = System::Drawing::Point(93, 112);
			this->buttonVerify->Name = L"buttonVerify";
			this->buttonVerify->Size = System::Drawing::Size(75, 23);
			this->buttonVerify->TabIndex = 6;
			this->buttonVerify->Text = L"Veritfy";
			this->buttonVerify->UseVisualStyleBackColor = true;
			this->buttonVerify->Click += gcnew System::EventHandler(this, &Main::buttonVerify_Click);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 149);
			this->Controls->Add(this->buttonVerify);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxHash);
			this->Controls->Add(this->buttonHash);
			this->Controls->Add(this->buttonFile);
			this->Controls->Add(this->textBoxFile);
			this->Controls->Add(this->label1);
			this->Name = L"Main";
			this->Text = L"Main";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonFile_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpenFileDialog^ ofd = gcnew OpenFileDialog();
				 ofd->Filter = "All Files|*.*";
				 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 {
					 return;
				 }
				 this->textBoxFile->Text = ofd->FileName;
	}
	private: System::Void buttonHash_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->textBoxFile->Text != "")
				 {
					 msclr::interop::marshal_context context;
					 std::string filename = context.marshal_as<std::string>(this->textBoxFile->Text);
					 std::string hash;
					 hash = Sha256::hash(filename);
					 this->textBoxHash->Text = context.marshal_as<String^>(hash);
				 }
	}
private: System::Void buttonVerify_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->textBoxFile->Text != "" && this->textBoxHash->Text != "")
			 {
				 msclr::interop::marshal_context context;
				 std::string filename = context.marshal_as<std::string>(this->textBoxFile->Text);
				 std::string hash;
				 hash = Sha256::hash(filename);
				 if (this->textBoxHash->Text == context.marshal_as<String^>(hash))
				 {
					 MessageBox::Show("Matches.");
				 }
				 else
				 {
					 MessageBox::Show("Doesn't match.");
				 }
			 }
}
};
}
