#ifndef __UTILS__
#define __UTILS__

// #include "app.h"
#include "../common/json.hpp"

using namespace std;
using json = nlohmann::json;

class AtomicString {
public:
	AtomicString();
	AtomicString(const string &str);
	~AtomicString();

	void set(const string &str);
	string get() const;
	bool empty() const;
	void clear();

private:
	mutable pthread_mutex_t mutex;
	string value;
};

extern bool write_raw_file(const string data, const string &filename);
extern bool write_json_file(const json data, const string &filename);

extern bool read_raw_file(string &data, const string &filename);
extern bool read_json_file(json &data, const string &filename);

extern bool download_json(const string &link, json &response, unsigned long timeout);
extern bool download_file(const string &link, const string &filename, unsigned long timeout);
extern long download_file_with_data_req(const string &link, const string &filename, string &datasend, unsigned long timeout);

extern void erase_all_string(string &main_string, string &erase_string);
extern void replace_all_string(string &main_string, string &find_string, string &repl_string);

extern void bytetoHexChar(uint8_t ubyte, uint8_t *uHexChar);
extern void bytestoHexChars(uint8_t *ubyte, int32_t len, uint8_t *uHexChar);
extern void hexChartoByte(uint8_t *uHexChar, uint8_t *ubyte);
extern void hexCharsToBytes(uint8_t *uHexChar, int32_t len, uint8_t *ubyte);

extern int get_net_info(const char *ifname, string &ip, string &mac);
extern string get_md5_file(const char *path);
extern int get_list_music(const char *path, json &list);
extern uint32_t get_usb_usage(const char *path);
extern uint32_t get_usb_remain(const char *path);
extern bool check_usb_encrypted(const char *script);
extern int touch_full_file(const char *file_name);
extern bool check_file_exist(const char *file_name);

extern int exec_prog(int, const char **);

extern vector<string> string_split(string &s, string delimiter);
extern size_t sizeOfFile(const char *url);

extern int systemCmd(const char *fmt, ...);
extern std::string systemStrCmd(const char *fmt, ...);
extern char *safe_strcpy(char *dest, const char *src, size_t dest_size);
extern void addNewlineToString(std::string &str, const std::string &newString);
extern string getFileName(const string &s);
extern bool appendStringToFile(const char *path, const string str);
extern string getLinesNotContainingWord(const char *path, const string str);
extern int hostnameToIp(char *hostname, char *ip);
extern bool endsWith(const string &fullString, const string &ending);
extern std::string xorEncryptDecrypt(const std::string &text, const std::string &key);

template<class T>
std::weak_ptr<T> make_weak_ptr(std::shared_ptr<T> ptr) {
	return ptr;
}

#endif	  //__UTILS__
