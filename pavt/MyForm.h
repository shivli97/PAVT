#pragma once

#include<cstdlib>
#include<Windows.h>
#include<conio.h>
#include<shellapi.h>
#include "clrpvt.h"
#include "slrpvt.h"
#include "lalrpvt.h"
#include "earley.h"
#include "cykpvt.h"
#include "ppvt.h"

namespace Project {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labelhead;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  grammar;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::RichTextBox^  textBox1;
	private: System::Windows::Forms::Button^  button4;

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
			this->labelhead = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->grammar = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labelhead
			// 
			this->labelhead->AutoSize = true;
			this->labelhead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelhead->Location = System::Drawing::Point(195, 21);
			this->labelhead->Name = L"labelhead";
			this->labelhead->Size = System::Drawing::Size(266, 16);
			this->labelhead->TabIndex = 0;
			this->labelhead->Text = L"Parsing Algorithms Visualization Tool";
			this->labelhead->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 58);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Grammar:";
			// 
			// grammar
			// 
			this->grammar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->grammar->Location = System::Drawing::Point(149, 55);
			this->grammar->Multiline = true;
			this->grammar->Name = L"grammar";
			this->grammar->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->grammar->Size = System::Drawing::Size(450, 167);
			this->grammar->TabIndex = 2;
			this->grammar->Tag = L"";
			this->grammar->Text = L"Type";
			this->grammar->Click += gcnew System::EventHandler(this, &MyForm::grammar_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label2->Location = System::Drawing::Point(12, 319);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(123, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Parsing Algorithm:";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label3->Location = System::Drawing::Point(12, 358);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(83, 17);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Description:";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Predictive Parsing", L"Simple LR Parsing", L"Canonical LR Parsing",
					L"Look-ahead LR Parsing", L"CYK Parsing", L"Earley Parsing"
			});
			this->comboBox1->Location = System::Drawing::Point(149, 316);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(450, 24);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button1->Location = System::Drawing::Point(219, 436);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Visualize";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button2->Location = System::Drawing::Point(325, 436);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 9;
			this->button2->Text = L"About";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label4->Location = System::Drawing::Point(12, 280);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 17);
			this->label4->TabIndex = 10;
			this->label4->Text = L"String:";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->textBox2->Location = System::Drawing::Point(149, 280);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(450, 23);
			this->textBox2->TabIndex = 11;
			this->textBox2->Text = L"Type";
			this->textBox2->Click += gcnew System::EventHandler(this, &MyForm::textBox2_Click);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->textBox3->Location = System::Drawing::Point(149, 240);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(294, 23);
			this->textBox3->TabIndex = 12;
			this->textBox3->Text = L"Or Upload";
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.6F));
			this->button3->Location = System::Drawing::Point(449, 240);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Browse";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->textBox1->Location = System::Drawing::Point(149, 355);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(450, 71);
			this->textBox1->TabIndex = 14;
			this->textBox1->Text = L"";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(524, 240);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 15;
			this->button4->Text = L"Upload";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(626, 466);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->grammar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->labelhead);
			this->Name = L"MyForm";
			this->Opacity = 0.9;
			this->Text = L"Welcome to PAVT";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
	if (this->comboBox1->Text == "Predictive Parsing")
	{
		this->textBox1->Text = "Predictive parsing was invented by Knuth (1971). It is a top-down parsing algorithm in which the production to be used in the next step of the derivation is selected on the basis of the next token in the program.";
		this->textBox1->Text += "It is a table-driven algorithm and does not use backtracking. \r\n \r\nKnuth, D. 1971. Top-down syntax analysis. Acta Informatica, 1(2): 79-110.";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 18;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 18;
		this->textBox1->SelectionLength = 303;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 319;
		this->textBox1->SelectionLength = 18;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 337;
		this->textBox1->SelectionLength = 1;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 338;
		this->textBox1->SelectionLength = 14;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));

	}
	else if (this->comboBox1->Text == "Simple LR Parsing")
	{
		this->textBox1->Text = "Simple LR parsing was invented by DeRemer (1971). It is a bottom-up table-driven parsing algorithm in which the production to be used in the next step of reduction is selected on the basis of one look-ahead token.";
		this->textBox1->Text+= "\r\n\r\nDeRemer, F.L. 1971. Simple LR(k) grammars.Communications of the ACM, 14(7): 453-460.	";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 17;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 17;
		this->textBox1->SelectionLength = 240;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 257;
		this->textBox1->SelectionLength = 27;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 284;
		this->textBox1->SelectionLength = 2;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 286;
		this->textBox1->SelectionLength = 23;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
	}
	else if (this->comboBox1->Text == "Canonical LR Parsing")
	{
		this->textBox1->Text = "Canonical LR parsing was invented by Knuth (1965). It is a bottom-up table-driven parsing algorithm in which the production to be used in the next step of reduction is selected on the basis of one look-ahead token.";
		this->textBox1->Text+= "\r\n\r\nKnuth, D.E. 1965. On the translation of languages from left to right.Information and Control, 8(6): 607-639.";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 20;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 20;
		this->textBox1->SelectionLength = 265;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 285;
		this->textBox1->SelectionLength = 24;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 309;
		this->textBox1->SelectionLength = 2;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 311;
		this->textBox1->SelectionLength = 16;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
	}
	else if (this->comboBox1->Text == "Look-ahead LR Parsing")
	{

		this->textBox1->Text = "Look-ahead LR parsing was invented by DeRemer (1969). It is a bottom-up table-driven parsing algorithm in which the production to be used in the next step of reduction is selected on the basis of one look-ahead token.";
		this->textBox1->Text+= "\r\n\r\nDeRemer, F. 1969. Practical Translators for LR(k) Languages. Ph.D. thesis, Massachusetts Institute of Technology.";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 21;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 21;
		this->textBox1->SelectionLength = 214;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 235;
		this->textBox1->SelectionLength =43;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 278;
		this->textBox1->SelectionLength = 55;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
	}
	else if (this->comboBox1->Text == "Earley Parsing")
	{
		this->textBox1->Text = "Earley parsing was invented by Earley (1968). It uses dynamic programming to serially arrange the tokens according to the productions of the grammar to obtain the full program.";
		this->textBox1->Text+= "It can be used to parse all context-free languages and hence is a universal parsing algorithm.\r\n\r\nEarley, J. 1968. An Efficient Context-Free Parsing Algorithm. Ph.D. thesis, Carnegie-Mellon University.";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 14;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 14;
		this->textBox1->SelectionLength = 276;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 289;
		this->textBox1->SelectionLength = 45;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 334;
		this->textBox1->SelectionLength = 50;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
	}
	else if (this->comboBox1->Text == "CYK Parsing")
	{
		this->textBox1->Text = "CYK parsing was invented independently by Cocke (1970), Younger (1967) and Kasami (1969). It uses dynamic programming to check if substrings of the program can be parsed according to the grammar.";
		this->textBox1->Text += "The algorithm starts with substrings comprising of single tokens and incrementally builds the full program. It can be used to parse all context-free languages and hence is a universal parsing algorithm.";
		this->textBox1->Text += "\r\n\r\nCocke, J. and Schwartz, J. T. 1970. Programming Languages and their Compilers: Preliminary Notes. 2nd ed., Technical report, New York University.";
		this->textBox1->Text += "\r\nKasami, T. 1969. An Efficient Recognition and Syntax Analysis Algorithm for Context-Free Languages. AFCRL-65-758, Technical report, Air Force Cambridge Research Laboratory.";
		this->textBox1->Text += "\r\nYounger, D. H. 1967. Recognition and parsing of context-free languages in time n^3. Information and Control, 10(2): 189-208.";
		this->textBox1->SelectionStart = 0;
		this->textBox1->SelectionLength = 11;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 11;
		this->textBox1->SelectionLength = 423;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 434;
		this->textBox1->SelectionLength = 62;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 496;
		this->textBox1->SelectionLength = 66;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 562;
		this->textBox1->SelectionLength = 83;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 645;
		this->textBox1->SelectionLength = 154;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));
		this->textBox1->SelectionStart = 799;
		this->textBox1->SelectionLength = 27;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Italic));
		this->textBox1->SelectionStart = 827;
		this->textBox1->SelectionLength = 2;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold));
		this->textBox1->SelectionStart = 829;
		this->textBox1->SelectionLength = 34;
		this->textBox1->SelectionFont = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10));

	}
} 

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	MessageBox::Show("Developed by Somya Sangal, Shreya Kataria, Twishi Tyagi, Nidhi Gupta, Yukti Kirtani, Shivli Agrawal and Pinaki Chakraborty.",
		"PAVT-About", MessageBoxButtons::OK, MessageBoxIcon::Information);

}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	//system("C:\\Users\\SK\\Documents\\Visual Studio 2015\\Projects\\Project\\SLRPVT9.exe\\");

	StreamWriter^ sw = gcnew StreamWriter("grammar.txt");
	sw->WriteLine(this->grammar->Text);
	sw->Close();
	StreamWriter^ sw1 = gcnew StreamWriter("details.txt");
	sw1->WriteLine(this->textBox2->Text);
	sw1->Close();
	if (this->comboBox1->Text == "Predictive Parsing")
	{
		pred();
	}
	else if (this->comboBox1->Text == "Simple LR Parsing")
	{
		slr();
	}
	else if (this->comboBox1->Text == "Canonical LR Parsing")
	{
		clr();
	}
	else if (this->comboBox1->Text == "Look-ahead LR Parsing")
	{
		lalr();
	}
	else if (this->comboBox1->Text == "Earley Parsing")
	{
		earley();
	}
	else if (this->comboBox1->Text == "CYK Parsing")
	{
		cyk();
	}
	
	/*CFileDialog l_fDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, "Text Files (*.txt)|*.txt|Comma Separated Values(*.csv)|*.csv||");
	int iRet = l_fDlg.DoModal();
	CString l_strFileName;
	l_strFileName = l_fDlg.GetPathName();

	if (iRet == IDOK) {
		try
		{
			CStdioFile file(_T(l_strFileName), CFile::modeRead);
			CString str, contentstr = _T("");

			while (file.ReadString(str))
			{
				contentstr += str;
				contentstr += _T("\n");
			}
		}
		catch (CException* e)
		{
			MessageBox(_T("Error"));
			e->Delete();
		}
	}*/
}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	Stream^ myStream;
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "c:\\";
	openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		
		if ((myStream = openFileDialog1->OpenFile()) != nullptr)
		{
			this->textBox3->Text =openFileDialog1->FileName;
			// Insert code to read the stream here.
			myStream->Close();
		}
	}
}

private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (this->textBox3->Text!="Or Upload")
	{
		StreamReader^ sw = gcnew StreamReader(this->textBox3->Text);
		this->grammar->Text = sw->ReadToEnd();
		sw->Close();
	}
}
private: System::Void textBox2_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if(this->textBox2->Text=="Type")
		this->textBox2->Clear();
}
private: System::Void grammar_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (this->grammar->Text == "Type")
		this->grammar->Clear();
}
};
}
