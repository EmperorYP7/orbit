// Copyright (c) 2020 The Orbit Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ORBIT_GL_SAMPLING_REPORT_H_
#define ORBIT_GL_SAMPLING_REPORT_H_

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "CallstackData.h"
#include "CallstackTypes.h"
#include "SamplingProfiler.h"
#include "SamplingReportDataView.h"

class SamplingReport {
 public:
  explicit SamplingReport(SamplingProfiler sampling_profiler, const CallstackData* callstack_data);
  void UpdateReport(SamplingProfiler profiler, const CallstackData* callstack_data);
  [[nodiscard]] std::vector<SamplingReportDataView>& GetThreadReports() { return thread_reports_; };
  void SetCallstackDataView(CallStackDataView* data_view) { callstack_data_view_ = data_view; };
  void OnSelectAddress(uint64_t address, ThreadID thread_id);
  void IncrementCallstackIndex();
  void DecrementCallstackIndex();
  [[nodiscard]] std::string GetSelectedCallstackString() const;
  void SetUiRefreshFunc(std::function<void()> func) { ui_refresh_func_ = std::move(func); };
  [[nodiscard]] bool HasCallstacks() const { return selected_sorted_callstack_report_ != nullptr; };
  [[nodiscard]] bool HasSamples() const {
    return callstack_data_ != nullptr && callstack_data_->GetCallstackEventsSize() > 0;
  }
  void ClearReport();

 protected:
  void FillReport();
  void OnCallstackIndexChanged(size_t index);
  void UpdateDisplayedCallstack();

 protected:
  SamplingProfiler profiler_;
  const CallstackData* callstack_data_;
  std::vector<SamplingReportDataView> thread_reports_;
  CallStackDataView* callstack_data_view_;

  uint64_t selected_address_;
  ThreadID selected_thread_id_;
  std::shared_ptr<SortedCallstackReport> selected_sorted_callstack_report_;
  size_t selected_callstack_index_;
  std::function<void()> ui_refresh_func_;
};

#endif  // ORBIT_GL_SAMPLING_REPORT_H_
