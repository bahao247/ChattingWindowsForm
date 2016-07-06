// FormatterText.h

#pragma once

using namespace System;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters;
using namespace System::Runtime::Serialization::Formatters::Binary;

namespace FormatterText {
	[Serializable]
	public ref class StructChat
	{
		// TODO: Add your methods for this class here.
	public:
		String^ textChat;
		System::Drawing::Color^ mau;
		System::Drawing::Font^ fontChu;

	public: StructChat()//Mac dinh khong doi so
			{
				textChat = "";
				mau = Color::Green;
				fontChu =  gcnew System::Drawing::Font("Arial", 9, FontStyle::Regular);
			}

	public:StructChat(String ^ text, System::Drawing::Font^ font, Color^ color)
		   {
			   textChat = text;
			   mau = color;
			   fontChu = font;
		   }

		   //Get Obj data
	public: void GetObjectData(SerializationInfo^ info, StreamingContext strcxt)
			{
				info->AddValue("text", textChat);
				info->AddValue("font", fontChu);
				info->AddValue("color", mau);
			}

			//Deserialize
	public:StructChat(SerializationInfo info, StreamingContext strcxt)
		   {
			   textChat = (String^)info.GetValue("text", String::typeid);
			   fontChu = (System::Drawing::Font^)info.GetValue("font", System::Drawing::Font::typeid);
			   mau = (System::Drawing::Color^)info.GetValue("color", System::Drawing::Color::typeid);
		   }
	};
}
