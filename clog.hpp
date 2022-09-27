#include <cstdio>

namespace filter {

bool IsSpecialCharacter(char c);
bool IsWordCharacter(char c);
bool IsFilterCharacter(char c);
bool VerifyFilter(const char *filter);

enum FilterState { NOT_MATCHED = 0, MATCHED, ABORTED };
FilterState MatchFilter(const char *line, const char *filter);

class CLogReader {
public:
  CLogReader() = default;
  ~CLogReader();

  bool Open(const char *filename); // открытие файла, false - ошибка
  void Close();                    // закрытие файла

  bool SetFilter(const char *filter); // установка фильтра строк, false - ошибка
  bool GetNextLine(char *buf, // запрос очередной найденной строки,
                   const int bufsize); // buf - буфер, bufsize - максимальная
                                       // длина false - конец файла или ошибка
private:
  FILE *stream_;
  char *filter_;
};

} // namespace filter
