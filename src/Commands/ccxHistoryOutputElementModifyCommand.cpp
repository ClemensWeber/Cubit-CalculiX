#include "ccxHistoryOutputElementModifyCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxHistoryOutputElementModifyCommand::ccxHistoryOutputElementModifyCommand()
{}

ccxHistoryOutputElementModifyCommand::~ccxHistoryOutputElementModifyCommand()
{}

std::vector<std::string> ccxHistoryOutputElementModifyCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("modify historyoutput <value:label='output id',help='<output id>'> ");
  syntax.append("element ");
  syntax.append("[name <string:type='unquoted', number='1', label='name', help='<name>'>] " );
  syntax.append("[block <value:label='block id',help='<block id>'>] ");
  syntax.append("[frequency <value:label='frequency',help='<frequency>'>] ");
  syntax.append("[frequencyf <value:label='frequencyf',help='<frequencyf>'>] ");
  syntax.append("[{totals_yes|totals_only|totals_no} ");
  syntax.append("[{global_yes|global_no} ");
  //syntax.append("[TIME_POINTS {yes|no} ");
  syntax.append("[{key_on|key_off} [S] [SVF] [E] [ME] [PEEQ] [CEEQ] [ENER] [SDV] [HFL] [HFLF] [COORD] [ELSE] [ELKE] [EVOL] [EMAS] [EBHE] [CENT]]");
  syntax_list.push_back(syntax);

  return syntax_list;
}

std::vector<std::string> ccxHistoryOutputElementModifyCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx ";
  help[0].append("modify historyoutput <output id> ");
  help[0].append("node ");
  help[0].append("[name <name>] " );
  help[0].append("[block <block id>] ");
  help[0].append("[frequency <frequency>] ");
  help[0].append("[frequencyf <frequencyf>] ");
  help[0].append("[{totals_yes|totals_only|totals_no} ");
  help[0].append("[{global_yes|global_no} ");
  //help[0].append("[TIME_POINTS {yes|no} ");
  help[0].append("[{key_on|key_off} [S] [SVF] [E] [ME] [PEEQ] [CEEQ] [ENER] [SDV] [HFL] [HFLF] [COORD] [ELSE] [ELKE] [EVOL] [EMAS] [EBHE] [CENT]]");

  return help;
}

std::vector<std::string> ccxHistoryOutputElementModifyCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxHistoryOutputElementModifyCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<std::string> options;
  std::vector<int> options_marker;
  int output_id;
  std::string name;
  int block_value;
  std::string block;
  int frequency_value;
  std::string frequency;
  int frequencyf_value;
  std::string frequencyf;
  std::string totals;
  std::string global;

  data.get_value("output id", output_id);

  if (data.get_string("name", name))
  {
    options_marker.push_back(1);
    options.push_back(name);
    if (!ccx_iface.modify_historyoutput(output_id, 0, options, options_marker))
    {
      output = "Changing Name Failed!\n";
      PRINT_ERROR(output.c_str());
    }  
    options.clear();
    options_marker.clear();
  }

  if (!data.get_value("block id", block_value))
  {
    block = "";
    options_marker.push_back(0);
  }
  else
  {
    block = std::to_string(block_value);
    options_marker.push_back(1);
  }
  options.push_back(block);
  
  if (!data.get_value("frequency", frequency_value))
  {
    frequency = "";
    options_marker.push_back(0);
  }
  else
  {
    frequency = std::to_string(frequency_value);
    options_marker.push_back(1);
  }
  options.push_back(frequency);
  
  if (!data.get_value("frequencyf", frequencyf_value))
  {
    frequencyf = "";
    options_marker.push_back(0);
  }
  else
  {
    frequencyf = std::to_string(frequencyf_value);
    options_marker.push_back(1);
  }
  options.push_back(frequencyf);
  
  if (data.find_keyword("TOTALS_YES"))
  {
    totals = "YES";
    options_marker.push_back(1);
  }else if (data.find_keyword("TOTALS_ONLY"))
  {
    totals = "ONLY";
    options_marker.push_back(1);
  }else if (data.find_keyword("TOTALS_NO"))
  {
    totals = "";
    options_marker.push_back(1);
  }else{
    totals = "";
    options_marker.push_back(0);
  }
  options.push_back(totals);

  if (data.find_keyword("GLOBAL_YES"))
  {
    global = "YES";
    options_marker.push_back(1);
  }else if (data.find_keyword("GLOBAL_NO"))
  {
    global = "";
    options_marker.push_back(1);
  }else{
    global = "";
    options_marker.push_back(0);
  }
  options.push_back(global);

  // timepoints
  options.push_back("");
  options_marker.push_back(0);

  //keys
  if (data.find_keyword("KEY_OFF"))
  {
    if (data.find_keyword("S"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("SVF"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("E"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ME"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("PEEQ"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("CEEQ"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ENER"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("SDV"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("HFL"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("HFLF"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("COORD"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ELSE"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ELKE"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EVOL"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EMAS"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EBHE"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("CENT"))
    {
      options.push_back("");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
  }else if (data.find_keyword("KEY_ON"))
  {
    if (data.find_keyword("S"))
    {
      options.push_back("S");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("SVF"))
    {
      options.push_back("SVF");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("E"))
    {
      options.push_back("E");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ME"))
    {
      options.push_back("ME");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("PN"))
    {
      options.push_back("PN");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("PEEQ"))
    {
      options.push_back("PEEQ");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("CEEQ"))
    {
      options.push_back("CEEQ");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ENER"))
    {
      options.push_back("ENER");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("SDV"))
    {
      options.push_back("SDV");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("HFL"))
    {
      options.push_back("HFL");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("HFLF"))
    {
      options.push_back("HFLF");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ELSE"))
    {
      options.push_back("ELSE");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("ELKE"))
    {
      options.push_back("ELKE");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EVOL"))
    {
      options.push_back("EVOL");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EMAS"))
    {
      options.push_back("EMAS");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("EBHE"))
    {
      options.push_back("EBHE");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
    if (data.find_keyword("CENT"))
    {
      options.push_back("CENT");
      options_marker.push_back(1);
    }else
    {
      options.push_back("");
      options_marker.push_back(0);
    }
  }else
  {
    for (size_t i = 6; i < 23; i++)
    {
      options.push_back("");
      options_marker.push_back(0);
    }
  }
  
  if (!ccx_iface.modify_historyoutput(output_id, 2, options, options_marker))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
    
  return true;
}