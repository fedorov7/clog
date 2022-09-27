#include <cstdio>

namespace filter {

bool IsSpecialCharacter(char c);
bool IsWordCharacter(char c);
bool IsFilterCharacter(char c);
bool VerifyFilter(const char *filter);
bool MatchFilter(const char *line, const char *filter);

class CLogReader {
public:
  CLogReader(unsigned int line_lenght_max = 4096);
  ~CLogReader();

  bool Open(const char *filename); // открытие файла, false - ошибка
  void Close();                    // закрытие файла

  bool SetFilter(const char *filter); // установка фильтра строк, false - ошибка
  bool GetNextLine(char *buf, // запрос очередной найденной строки,
                   const int bufsize); // buf - буфер, bufsize - максимальная
                                       // длина false - конец файла или ошибка
private:
  FILE *stream_;
  char *buffer_;
  unsigned int buffer_size_;
  char *filter_;
};

} // namespace filter
