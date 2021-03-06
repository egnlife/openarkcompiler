/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MAPLE_IR_INCLUDE_OPTION_H
#define MAPLE_IR_INCLUDE_OPTION_H
#include <string>
#include <vector>
#include "mempool.h"
#include "mempool_allocator.h"
#include "parser_opt.h"
#include "types_def.h"

namespace maple {
constexpr uint32 kNoDecouple = 0;
constexpr uint32 kConservativeDecouple = 1;
constexpr uint32 kRadicalDecouple = 2;
constexpr uint32 kNoLazyBinding = 0;
constexpr uint32 kLazyBindingUseConditionCall = 1;
constexpr uint32 kLazyBindingUseSegv = 2;
class Options {
 public:
  explicit Options(maple::MemPool &memPool) : optionAlloc(&memPool) {}

  bool ParseOptions(int argc, char **argv, std::string &fileName) const;
  ~Options() = default;

  void DumpOptions() const;
  const std::vector<std::string> &GetSequence() const {
    return phaseSeq;
  }

  const std::string LastPhaseName() const {
    return phaseSeq.empty() ? "noopt" : phaseSeq[phaseSeq.size() - 1].c_str();
  }

  static bool dumpBefore;
  static bool dumpAfter;
  static std::string dumpPhase;
  static std::string skipPhase;
  static std::string skipFrom;
  static std::string skipAfter;
  static std::string dumpFunc;
  static bool quiet;
  static bool regNativeFunc;
  static bool regNativeDynamicOnly;
  static bool nativeWrapper;
  static std::string staticBindingList;
  static bool usePreg;
  static bool mapleLinker;
  static bool dumpMuidFile;
  static bool emitVtableImpl;
#if MIR_JAVA
  static bool skipVirtualMethod;
#endif
 private:
  MapleAllocator optionAlloc;
  std::vector<std::string> phaseSeq;
};
}  // namespace maple
#ifndef TRACE_PHASE
#define TRACE_PHASE (Options::dumpPhase.compare(PhaseName()) == 0)
#endif
#endif  // MAPLE_IR_INCLUDE_OPTION_H
