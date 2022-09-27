#include "clog.hpp"

#include <cstdlib>
#include <cstring>

namespace filter {

bool IsSpecialCharacter(char c) {
  // *
  if (c == '*') {
    return true;
  }
  // ?
  if (c == '?') {
    return true;
  }
  return false;
}

bool IsWordCharacter(char c) {
  // 0-9
  if (c >= '0' && c <= '9') {
    return true;
  }
  // A-Z
  if (c >= 'A' && c <= 'Z') {
    return true;
  }
  // a-z
  if (c >= 'a' && c <= 'z') {
    return true;
  }
  return false;
}

bool IsFilterCharacter(char c) {
  if (IsSpecialCharacter(c)) {
    return true;
  }
  if (IsWordCharacter(c)) {
    return true;
  }
  return false;
}

bool VerifyFilter(const char *filter) {
  const char *ptr = filter;
  if (filter == NULL) {
    return false;
  }
  // Check inappropriate symbol contains
  while (*ptr != '\0') {
    if (!IsFilterCharacter(*ptr)) {
      return false;
    }
    ptr++;
  }
  return true;
}

FilterState MatchFilter(const char *line, const char *filter) {
  const char *line_ptr = line;
  const char *filter_ptr = filter;

  while (true) {
    // check if line length is bigger than buffer size
    if (*line_ptr == '\0') {
      return ABORTED;
    }
    // check if line is ending
    if (*line_ptr == '\n') {
      while (*filter_ptr == '*') {
        filter_ptr++;
      }
      if (*filter_ptr == '\0') {
        return MATCHED;
      }
      return NOT_MATCHED;
    }

    // recursive call with shifted line
    if (*filter_ptr == '*') {
      auto ret = MatchFilter(line_ptr + 1, filter_ptr);
      if (ret > 0) {
        return ret;
      }
      // skip trailing asterisks
      do {
        filter_ptr++;
      } while (*filter_ptr == '*');
      continue;
    }

    // skip one character
    if (*filter_ptr == '?') {
      filter_ptr++;
      line_ptr++;
      continue;
    }

    if (*filter_ptr == *line_ptr) {
      filter_ptr++;
      line_ptr++;
      continue;
    }

    return NOT_MATCHED;
  }
}

CLogReader::~CLogReader() { Close(); }

bool CLogReader::Open(const char *filename) {
  stream_ = fopen(filename, "r");
  if (stream_ != NULL) {
    return true;
  }
  return false;
}

void CLogReader::Close() {
  if (stream_ != NULL) {
    fclose(stream_);
  }
  stream_ = NULL;
}

bool CLogReader::SetFilter(const char *filter) {
  if (!VerifyFilter(filter)) {
    return false;
  }
  filter_ = strdup(filter);
  if (filter_ == NULL) {
    return false;
  }
  return true;
}

bool CLogReader::GetNextLine(char *buf, const int bufsize) {
  if (stream_ == NULL) {
    return false;
  }
  while (true) {
    char *line = fgets(buf, bufsize, stream_);
    if (line == NULL) {
      return false;
    }
    auto ret = MatchFilter(line, filter_);
    if (ret == ABORTED) {
      // buffer size is not enought
      return false;
    }
    if (ret == MATCHED) {
      // buffer is matched
      return true;
    }
  }
}

} // namespace filter
