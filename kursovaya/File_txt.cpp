#include "File_txt.h"

File_txt::File_txt(string name)
{
	file_name = name;
}

File_txt::~File_txt()
{
	if (is.is_open())
		is.close();
	if (os.is_open())
		os.close();
}

bool File_txt::open_to_write()
{
	os.open(file_name);
	return os.is_open();
}

bool File_txt::open_to_read()
{
	is.open(file_name);
	return is.is_open();
}

void File_txt::remote()
{
	is.clear();
	os.clear();
	is.seekg(0, ios_base::beg);
	os.seekp(0, ios_base::beg);
}

