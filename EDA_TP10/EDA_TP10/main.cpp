
#include "LCD/Hitachi/hitachilcd.h"
#include "LCD/Allegro/allegrolcd.h"
#include "Utils.h"
void cortar(string &data, string &ans);


int main(int argc, char ** argv)
{

	if (argc > 2)
	{
		cout << ">> Input error: to many arguments." << endl;
		cout << ">> Only needed the host for parse.-" << endl;
		return -1;
	}

	if (argc < 2)
	{
		cout << ">> Input error: no host entered" << endl;
		cout << ">> Please enter host as parameter.-" << endl;
		return -1;
	}
	//hitachilcd lcdk;
	allegrolcd lcd(1.3,2.3);
	CursesClass cur;
	string file=getXML(lcd, cur, argv[1]);

	//client cl;
	//cl.startConnection(argv[1]);
	//if (cl.success()){
	//	//string msg = "GET /rss2/ultimasnoticias.xml HTTP/1.1\r\n";
	//	//cout << ">> Sending request... \n";
	//	//cout << msg << '\n';
	//	//string msg2 = "Host: www.telam.com.ar\r\n";
	//	//cout << ">> Sending request... \n";
	//	//cout << msg2 << '\n';
	//	//string msg3 = "\r\n";
	//
	//	//cl.send_message(msg.c_str(),msg.size());
	//	//cl.send_message(msg2.c_str(), msg2.size());
	//	//cl.send_message(msg3.c_str(), msg3.size());//Deliciosos magic numbers
	//	//cout << ">> Message sent \n";
	//	//string data_ans;
	//	//data_ans=cl.receiveMessage();
	//	//size_t it= 	data_ans.find_first_of("<?");
	//	//data_ans.erase(0, it);


	//	
	//}
	//else
	//	cout << "Couldnt connect" << endl;
	return 0;

}
