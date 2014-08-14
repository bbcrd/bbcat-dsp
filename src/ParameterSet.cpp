
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_LEVEL 0
#include "ParameterSet.h"

BBC_AUDIOTOOLBOX_START

ParameterSet::ParameterSet(const ParameterSet& obj)
{
  operator = (obj);
}

/*--------------------------------------------------------------------------------*/
/** Assignment operator
 */
/*--------------------------------------------------------------------------------*/
ParameterSet& ParameterSet::operator = (const ParameterSet& obj)
{
  values = obj.values;

  return *this;
}

/*--------------------------------------------------------------------------------*/
/** Merge operator
 */
/*--------------------------------------------------------------------------------*/
ParameterSet& ParameterSet::operator += (const ParameterSet& obj)
{
  std::map<std::string,std::string>::const_iterator it;

  for (it = obj.values.begin(); it != obj.values.end(); ++it)
  {
    values[it->first] = it->second;
  }

  return *this;
}

/*--------------------------------------------------------------------------------*/
/** Removal operator
 *
 * Removes any parameters specified on obj that exist in this object
 */
/*--------------------------------------------------------------------------------*/
ParameterSet& ParameterSet::operator -= (const ParameterSet& obj)
{
  std::map<std::string,std::string>::const_iterator it, it2;

  for (it = obj.values.begin(); it != obj.values.end(); ++it)
  {
    if ((it2 = values.find(it->first)) != values.end())
    {
      values.erase(it2);
    }
  }

  return *this;
}

std::string ParameterSet::ToString() const
{
  std::map<std::string,std::string>::const_iterator it;
  std::string str;

  for (it = values.begin(); it != values.end(); ++it)
  {
    if (it != values.begin()) Printf(str, ", ");
    Printf(str, "%s %s", it->first.c_str(), it->second.c_str());
  }

  return str;
}

/*--------------------------------------------------------------------------------*/
/** Set parameter
 *
 * @note any existing value with the same name will be overwritten
 *
 */
/*--------------------------------------------------------------------------------*/
void ParameterSet::Set(const std::string& name, const std::string& val)
{
  values[name] = val;
}

void ParameterSet::Set(const std::string& name, bool val)
{
  std::string str;
  Printf(str, "%u", val ? 1 : 0);
  Set(name, str);
}

void ParameterSet::Set(const std::string& name, sint_t val)
{
  std::string str;
  Printf(str, "%d", val);
  Set(name, str);
}

void ParameterSet::Set(const std::string& name, slong_t val)
{
  std::string str;
  Printf(str, "%ld", val);
  Set(name, str);
}

void ParameterSet::Set(const std::string& name, double val)
{
  std::string str;
  Printf(str, "%0.32le", val);
  Set(name, str);
}

/*--------------------------------------------------------------------------------*/
/** Get value
 *
 * @param name parameter name
 * @param val reference to value to be set
 *
 * @return true if parameter found and value extracted
 */
/*--------------------------------------------------------------------------------*/
bool ParameterSet::Get(const std::string& name, std::string& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  if (it != values.end()) val = it->second;
  return (it != values.end());
}

bool ParameterSet::Get(const std::string& name, bool& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  uint_t n;
  bool   success = false;

  if ((it != values.end()) && (sscanf(it->second.c_str(), "%u", &n) > 0))
  {
    val = (n != 0);
    success = true;
  }

  return success;
}

bool ParameterSet::Get(const std::string& name, sint_t& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return ((it != values.end()) && (sscanf(it->second.c_str(), "%d", &val) > 0));
}

bool ParameterSet::Get(const std::string& name, uint_t& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return ((it != values.end()) && (sscanf(it->second.c_str(), "%u", &val) > 0));
}

bool ParameterSet::Get(const std::string& name, slong_t& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return ((it != values.end()) && (sscanf(it->second.c_str(), "%ld", &val) > 0));
}

bool ParameterSet::Get(const std::string& name, ulong_t& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return ((it != values.end()) && (sscanf(it->second.c_str(), "%lu", &val) > 0));
}

bool ParameterSet::Get(const std::string& name, double& val) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return ((it != values.end()) && (sscanf(it->second.c_str(), "%lf", &val) > 0));
}

std::string ParameterSet::Raw(const std::string& name, const std::string& defval) const
{
  const std::map<std::string,std::string>::const_iterator it = values.find(name);
  return (it != values.end()) ? it->second : defval; 
}

BBC_AUDIOTOOLBOX_END