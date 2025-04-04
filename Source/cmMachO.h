/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.rst or https://cmake.org/licensing for details.  */
#pragma once

#include "cmConfigure.h" // IWYU pragma: keep

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include <mach/machine.h>

#if !defined(CMake_USE_MACH_PARSER)
#  error "This file may be included only if CMake_USE_MACH_PARSER is enabled."
#endif

class cmMachOInternal;

/** \class cmMachO
 * \brief Executable and Link Format (Mach-O) parser.
 */
class cmMachO
{
public:
  struct MachHeader
  {
    cpu_type_t CpuType;
    cpu_subtype_t CpuSubType;
    uint32_t FileType;
  };
  class StringList : public std::vector<std::string>
  {
  };

  /** Construct with the name of the Mach-O input file to parse.  */
  cmMachO(char const* fname);

  /** Destruct.   */
  ~cmMachO();

  /** Get the error message if any.  */
  std::string const& GetErrorMessage() const;

  /** Boolean conversion.  True if the Mach-O file is valid.  */
  explicit operator bool() const { return this->Valid(); }

  /** Get Install name from binary **/
  bool GetInstallName(std::string& install_name);

  /** Print human-readable information about the Mach-O file.  */
  void PrintInfo(std::ostream& os) const;

  /** Get the architectural header(s) from the Mach-O file.  */
  std::vector<struct MachHeader> GetHeaders() const { return this->Headers; }

  /** Get a list of the recognized architectures present in the Mach-O file
   * in the order in which they are found.
   */
  StringList GetArchitectures() const;

private:
  friend class cmMachOInternal;
  bool Valid() const;
  std::unique_ptr<cmMachOInternal> Internal;
  std::vector<struct MachHeader> Headers;
};
