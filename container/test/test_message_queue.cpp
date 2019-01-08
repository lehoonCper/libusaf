#include "../message_queue.h"
#include <stdarg.h>
using namespace USAF;


std::string & std_string_format(std::string & _str, const char * _Format, ...){
	va_list marker = NULL;
	va_start(marker, _Format);
 
	int num_of_chars = _vscprintf(_Format, marker);
 
	if (num_of_chars > _str.capacity()){
		_str.resize(num_of_chars + 1);
	}
 
	vsprintf((char *) _str.c_str(), _Format, marker);
 
	va_end(marker);
	return _str;
}

int main()
{
    MessageQueue<std::string> mq(4);

    for(int i = 0; i < 100; ++i)
    {
        string str;
        int j = i;
        std_string_format(str, "value=%d", j);
        mq.put(i,str);
    }

    string val;
    while(mq.get(1,val))
    {
        cout << val << endl;
    }

    return 0;
}