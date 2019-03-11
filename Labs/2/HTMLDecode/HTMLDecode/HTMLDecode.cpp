#include "pch.h"
#include "Decoder.h"
#include <iostream>

int main()
{
	string html;
	while (getline(cin, html))
	{
		cout << HtmlDecode(html);
		if (!cin.eof())
		{
			cout << endl;
		}
	}
}