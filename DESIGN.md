# SimpleLSM (v0.1) Design Document

## 1. Design Philosophy

This project aims to build a Log-Structured Merge-Tree (LSM-Tree) key-value storage engine from scratch. Since system programming is highly complex, the v0.1 release strictly follows the **"Make it work, then make it right, then make it fast"** philosophy.

### 1.1 Core Goals for v0.1
*   **Correctness First**: No data loss or silent corruption under any circumstances.
*   **Crash-Safety**: Rely on Write-Ahead Logging (WAL) and `fsync` to guarantee that acknowledged writes survive process crashes (`kill -9`) or sudden power failures.
*   **Extreme Simplicity**:
    *   Use a single global mutex (`std::mutex`) to protect all operations. No concurrent reads/writes in v0.1.
    *   Use standard containers (`std::map`) instead of complex lock-free SkipLists.
    *   Use fixed-length binary encoding instead of Varints for easier debugging and hexdumping.
    *   Use flat SSTables with linear scanning instead of Data Blocks, Block Indexes, and Bloom Filters.

---

## 2. Architecture Overview

```text
  [ Client ]
      | (Put / Get / Delete)
      v
+---------------------------------------------------+
|                  SimpleLSM (v0.1)                 |
|               (Global Mutex Locked)               |
|                                                   |
|  1. Write  ------> [ WAL (Write-Ahead Log) ]      |
|                      | (fsync)                    |
|  2. Update ------> [ Active Memtable ]            |
|                      | (when size > threshold)    |
|                      v                            |
|                  [ Immutable Memtable ]           |
|                      | (Sync Flush)               |
|                      v                            |
|                  [ SSTable File 1 ]               |
|                  [ SSTable File 2 ]               |
|                                                   |
|  * Meta-data ----> [ MANIFEST File ]              |
+---------------------------------------------------+