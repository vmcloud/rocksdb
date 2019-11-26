// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <iostream>
#include <rocksdb/compaction_filter.h>
#include <rocksdb/db.h>
#include <rocksdb/merge_operator.h>
#include <rocksdb/options.h>
#include "gflags/gflags.h"

#define gflags google

//const char *db_name = "/aa4eb98b-6641-4d96-8601-ebc21579d53d/ifileDB";
DEFINE_string(db_name, "", "database path to compact");

int main(int argc, char *argv[]) {
  gflags::SetUsageMessage("manual compact database");
  gflags::SetVersionString("1.0.0");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  rocksdb::DB* raw_db;
  rocksdb::Status status;

  std::cout << "database path is: " << FLAGS_db_name << std::endl;
  rocksdb::Options options;
  //options.create_if_missing = true;
  options.target_file_size_base = uint64_t(4) << 30;
  options.max_bytes_for_level_base = uint64_t(1024) << 20;
  //options.compaction_readahead_size = size_t(8) << 20;
  options.max_background_jobs = 32;
  options.max_subcompactions = 4;
  status = rocksdb::DB::Open(options, FLAGS_db_name, &raw_db);
  std::cout << "open ok: " << status.ok() << ", status code: " << status.code() << std::endl;
  std::unique_ptr<rocksdb::DB> db(raw_db);

  status = db->CompactRange(rocksdb::CompactRangeOptions(), nullptr, nullptr);
  std::cout << "compact ok: " << status.ok() << ", status code: " << status.code() << std::endl;
  gflags::ShutDownCommandLineFlags();
}
