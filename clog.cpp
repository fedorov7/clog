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

bool MatchFilter(const char *line, const char *filter) {
  const char *line_ptr = line;
  const char *filter_ptr = filter;

  while (true) {
    // check if line is ending
    if (*line_ptr == '\n') {
      while (*filter_ptr == '*') {
        filter_ptr++;
      }
      if (*filter_ptr == '\0') {
        return true;
      }
      return false;
    }

    // recursive call with shifted line
    if (*filter_ptr == '*') {
      if (MatchFilter(line_ptr + 1, filter_ptr)) {
        return true;
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

    return false;
  }
}

CLogReader::CLogReader(unsigned int line_length_max) {
  if (line_length_max == 0) {
    buffer_size_ = 4096;
  } else {
    buffer_size_ = line_length_max;
  }
  buffer_ = static_cast<char *>(malloc(buffer_size_));
}

CLogReader::~CLogReader() {
  Close();
  if (buffer_ != NULL) {
    free(buffer_);
  }
}

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
  if (buffer_ == NULL) {
    return false;
  }
  while (true) {
    char *line = fgets(buffer_, buffer_size_, stream_);
    if (line == NULL) {
      return false;
    }
    if (MatchFilter(line, filter_)) {
      // check buffer size
      if (strlen(line) >= bufsize) {
        return false;
      }
      strncpy(buf, line, bufsize);
      return true;
    }
  }
}

} // namespace filter
