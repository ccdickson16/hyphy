/*
 
 HyPhy - Hypothesis Testing Using Phylogenies.
 
 Copyright (C) 1997-now
 Core Developers:
 Sergei L Kosakovsky Pond (sergeilkp@icloud.com)
 Art FY Poon    (apoon@cfenet.ubc.ca)
 Steven Weaver (sweaver@temple.edu)
 
 Module Developers:
 Lance Hepler (nlhepler@gmail.com)
 Martin Smith (martin.audacis@gmail.com)
 
 Significant contributions from:
 Spencer V Muse (muse@stat.ncsu.edu)
 Simon DW Frost (sdf22@cam.ac.uk)
 
 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */

#include "string_file_wrapper.h"

StringFileWrapper::StringFileWrapper (_String *string, FILE *file) {
  string_buffer = string;
  file_buffer = file;
}

StringFileWrapper& StringFileWrapper::operator << (const char* buffer) {
  if (string_buffer) {
    *string_buffer << buffer;
  } else if (file_buffer) {
    fprintf (file_buffer, buffer);
  }
  return *this;
}

StringFileWrapper& StringFileWrapper::operator << (const char letter) {
  if (string_buffer) {
    *string_buffer << letter;
  } else if (file_buffer) {
    fputc (letter, file_buffer);
  }
  return *this;
}

StringFileWrapper& StringFileWrapper::operator << (const _String& buffer) {
  if (string_buffer) {
    *string_buffer << buffer;
  } else if (file_buffer) {
    fprintf (file_buffer, "%s", (const char*)buffer);
  }
  return *this;
}

StringFileWrapper& StringFileWrapper::operator << (const _String* buffer) {
  return (*this) << *buffer;
}

StringFileWrapper& StringFileWrapper::operator << (const StringFileWrapperConstants& special) {
  if (string_buffer) {
    switch (special) {
      case kStringFileWrapperNewLine:
        *string_buffer << '\n';
        break;
      case kStringFileWrapperLinefeed:
        *string_buffer << '\r';
        break;
      case kStringFileWrapperTab:
        *string_buffer << '\t';
        break;
    }
  } else if (file_buffer) {
    switch (special) {
      case kStringFileWrapperNewLine:
        fputc ('\n', file_buffer);
        break;
      case kStringFileWrapperLinefeed:
        fputc ('\r', file_buffer);
       break;
      case kStringFileWrapperTab:
        fputc ('\t', file_buffer);
       break;
    }
  }
  return *this;
}

