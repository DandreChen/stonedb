/* Copyright (c) 2022 StoneAtom, Inc. All rights reserved.
   Use is subject to license terms

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1335 USA
*/
#ifndef TIANMU_EXPORTER_DATA_EXPORTER_TXT_H_
#define TIANMU_EXPORTER_DATA_EXPORTER_TXT_H_
#pragma once

#include "exporter/data_exporter.h"
#include "system/io_parameters.h"

namespace Tianmu {
namespace exporter {

class DEforTxt : public DataExporter {
 public:
  DEforTxt(const system::IOParameters &iop);
  void PutNull() override {
    WriteNull();
    WriteValueEnd();
  }

  void PutText(const types::BString &str) override;

  void PutBin(const types::BString &str) override;

  void PutNumeric(int64_t num) override;

  void PutDateTime(int64_t dt) override;

  void PutRowEnd() override;

 protected:
  void WriteStringQualifier() { /*data_exporter_buf_->WriteIfNonzero(str_q);*/
  }
  void WriteDelimiter() { data_exporter_buf_->WriteIfNonzero(delimiter_); }
  void WriteNull() { WriteString(nulls_str_.c_str(), (int)nulls_str_.length()); }
  void WriteString(const types::BString &str) { WriteString(str, str.size()); }
  size_t WriteString(const types::BString &str, int len);
  void WriteChar(char c, uint repeat = 1) { std::memset(data_exporter_buf_->BufAppend(repeat), c, repeat); }
  void WritePad(uint repeat) { WriteChar(' ', repeat); }
  void WriteValueEnd() {
    if (cur_attr_ == no_attrs_ - 1)
      cur_attr_ = 0;
    else {
      WriteDelimiter();
      cur_attr_++;
    }
  }

  uchar delimiter_, str_qualifier_, escape_character_;
  uchar line_terminator_;
  std::string nulls_str_, escaped_;
  CHARSET_INFO *destination_charset_;
};

}  // namespace exporter
}  // namespace Tianmu

#endif  // TIANMU_EXPORTER_DATA_EXPORTER_TXT_H_
