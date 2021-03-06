/*                                   -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 * debugging commands
 */
#include "e_cardlist.h"
#include "u_lang.h"
#include "c_comand.h"
#include "globals.h"
#include "e_node.h"
#include "e_subckt.h"
#include "u_nodemap.h"
#include "io_matrix.h"
#include "u_sim_data.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "gcuf_compat.h"
using namespace std;
/*--------------------------------------------------------------------------*/
namespace { //
/*--------------------------------------------------------------------------*/
#if 0
void volts_load( fstream *in, CARD_LIST* )
{ untested();
  // fixme. -nan
  std::string inss;
  double ind;
  uint_t i=1;
  double Last;
  *in >> Last;
  trace1("volts_load", Last);
//  assert(CKT_BASE::_sim->vdc());
  CKT_BASE::_sim->_last_Time = Last;
  while ( ! (in->eof() ) ){ untested();
    assert( i< CKT_BASE::_sim->_total_nodes +2 + CKT_BASE::_sim->_adp_nodes );
    *in >> skipws;

    if( '\n' ==  in->peek()
       ||' ' ==  in->peek() ){ untested();
      in->get();
    } else if( 'n' ==  in->peek() ){ untested();
      *in >> inss >> skipws;
      if(inss=="nan"){ untested();
        trace1(" putting nan ", i);
        CKT_BASE::_sim->vdc()[i] = NAN;
        i++;
      }
    } else if(*in >> ind){ untested();
      *in >> skipws;
      trace2(" putting ", i, ind);
      CKT_BASE::_sim->vdc()[i] = ind;
      ++i;
    } else { untested();
      //*in >> skipws >> inss;
      inss = (char) in->get();
      trace1((" garbage ->" + inss + "<- ").c_str(), (int)inss[0]);
    }
  }
}
/*--------------------------------------------------------------------------*/
void volts_save(CS&, OMSTREAM _out, CARD_LIST*)
{ untested();
  CARD_LIST::card_list.precalc_first();

  //_out.setfloatwidth(7);
  switch (ENV::run_mode) { untested();
  case rPRE_MAIN:
    unreachable();
    return;
  case rPRESET:
    /* do nothing */
    return;
  case rPIPE:		untested();
  case rBATCH:		itested();
  case rINTERACTIVE:	itested();
  case rSCRIPT:
    /* keep going */
    break;
  }

  if (!OPT::language) { untested();
    throw Exception("no language");
  }else{ untested();
  }

  if (! CKT_BASE::_sim->_nstat ) return;
  trace2( "save",  CKT_BASE::_sim->_total_nodes , CKT_BASE::_sim->_adp_nodes );
  
  _out <<  CKT_BASE::_sim->_last_Time << "\n";

  for ( uint_t i = 1;  CKT_BASE::_sim->_total_nodes + 1 + CKT_BASE::_sim->_adp_nodes > i ; ++i){ untested();
    _out <<  CKT_BASE::_sim->vdc()[i] << "\n";
  }
  const NODE_MAP * nm = CARD_LIST::card_list.nodes();
  for (NODE_MAP::const_iterator i = nm->begin(); i != nm->end(); ++i) { untested();
    const CKT_NODE* s= (dynamic_cast<const CKT_NODE*>(i->second));
    if (i->first != "0" && s) { untested();
      _out << i->second->long_label() << " vector position " << 
        ", m_ " << s->m_() << " , matrix " << s->matrix_number() 
          << ", use number " << s->user_number() << 
         " x-Entry " <<  CKT_BASE::_sim->vdc()[s->matrix_number()] <<"\n";
    }else{ untested();
      _out << "Zero Node  "  << "\n";
    }
  }

  _out << CKT_BASE::_sim->_aa << "\n";
  _out << CKT_BASE::_sim->_lu << "\n";
  // cout << CKT_BASE::_sim->_acx << "\n";

  _out << "----------------------------------------- \n";
  //  out << CKT_BASE::_sim->_acx;

}


/*--------------------------------------------------------------------------*/
class CMD_LIST : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* Scope)
  { untested();
    std::string filename;
    cmd >> filename;
    fstream inFile(filename.c_str());
    if (inFile.fail()) { untested();
      cerr << "Unable to open " << filename << " for reading." << endl;
      return;
    }
    volts_load(&inFile, Scope);
    inFile.close();
  }
} p1;
DISPATCHER<CMD>::INSTALL d1(&command_dispatcher, "vloaddeb", &p1);
/*--------------------------------------------------------------------------*/
class CMD_SAVE : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* Scope)
  { untested();
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(3);
    out.outset(cmd);
    volts_save(cmd, out, Scope);
    out.outreset();
  }
} p2;
DISPATCHER<CMD>::INSTALL d2(&command_dispatcher, "vdeb", &p2);
/*--------------------------------------------------------------------------*/
#endif
class CMD_AA : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(3);
//    out.outset(cmd); redirection?

    // volts_save(cmd, out, Scope);
    //
    out << CKT_BASE::_sim->_aa << "\n";
//    out.outreset();
  }
} p3;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, "aa", &p3);
/*--------------------------------------------------------------------------*/
class CMD_LU : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(3);
//    out.outset(cmd); redirection?

    // volts_save(cmd, out, Scope);
    //
    out << CKT_BASE::_sim->_lu << "\n";
//    out.outreset();
  }
} p4;
DISPATCHER<CMD>::INSTALL d4(&command_dispatcher, "lu", &p4);
/*--------------------------------------------------------------------------*/
#if 0 // uf only...
class CMD_MSTAT: public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(30);
//    out.outset(cmd);

    CKT_BASE::_sim->init();
    for(unsigned i=0; i <= _sim->_total_nodes; ++i){ untested();
      for(unsigned j=0; j <= _sim->_total_nodes; ++j){ untested();
        assert(_sim->_aa.n(i,j)==_sim->_lu.n(i,j));
        out << _sim->_aa.n(i,j);
      }
      out << "\n";
    }

 //   out.outreset();
  }
} p5k;
DISPATCHER<CMD>::INSTALL d5k(&command_dispatcher, "mstat", &p5k);
#endif
/*--------------------------------------------------------------------------*/
class CMD_ACX: public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM out = IO::mstdout;
    out.setfloatwidth(30);
//    out.outset(cmd);

    out <<  "this doesnt make sense. run .ac with \"dm\" flag instead\n";
//    out.outreset();
  }
} p5;
DISPATCHER<CMD>::INSTALL d5(&command_dispatcher, "acx", &p5);
/*--------------------------------------------------------------------------*/
class CMD_ML : public CMD { //
public:
  void print(OMSTREAM, const CARD_LIST*);
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM _out = IO::mstdout;

    for(DISPATCHER<CARD*>::const_iterator i=model_dispatcher.begin();
        i!=model_dispatcher.end(); ++i)
    { untested();
      _out << i->first;
      _out << "\n";
    }
  }
} plm;
DISPATCHER<CMD>::INSTALL dlm(&command_dispatcher, "listmodels", &plm);
/*--------------------------------------------------------------------------*/
class CMD_NL : public CMD { //
public:
  void print(OMSTREAM, const CARD_LIST*);
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM _out = IO::mstdout;
    _out.setfloatwidth(3);
  //  _out.outset(cmd);

    _out << "name   ...\n";

    CKT_BASE::_sim->init();

    _out << "have " << _sim->_total_nodes
      << " nodes. model: " << _sim->_model_nodes
      << " sckt: " << _sim->_subckt_nodes
//      << " adp " << _sim->_adp_nodes
      << "\n";
    for(unsigned k=0; k<= (unsigned)_sim->_total_nodes; ++k){ untested();
      trace2( "CMD_NL::do_it", k, _sim->_nm[k]);
    }
    _out << "\n";
    print(_out, &CARD_LIST::card_list);
    //_out.reset();
  }
} p6;
DISPATCHER<CMD>::INSTALL d6(&command_dispatcher, "nodelist|listnodes", &p6);
/*--------------------------------------------------------------------------*/
#define CKT_NODE NODE
void CMD_NL::print( OMSTREAM _out, const CARD_LIST* scope){ untested();
  assert(scope);
  const NODE_MAP * nm = scope->nodes();
  for (NODE_MAP::const_iterator i = nm->begin(); i != nm->end(); ++i) { untested();
    if (i->first != "0") { untested();
      stringstream s;
      _out << i->first << " ";

      s << setw(8) << i->second->long_label() << " ";
      _out << s.str();

      const CKT_NODE* c = (dynamic_cast<const CKT_NODE*>(i->second));
//      const ADP_NODE* a = (dynamic_cast<const ADP_NODE*>(i->second));
      if (c){ untested();
        _out << "matrix_number " << c->matrix_number()
             << ", user_number " << c->user_number() << " nm[t] ";
        _out << " vdc "; // <<  CKT_BASE::_sim->vdc()[c->matrix_number()];
        // _v0 is not allocated right now
#if 0 // uf
       } else if (a) { untested();
         _out << "adp " << a->m_() << " " <<  _sim->_total_nodes;
#endif
      }
      _out  <<"\n";
    }else{ untested();
      // _out << "Zero Node  "  << "\n";
    }
  }

  for (CARD_LIST::const_iterator i = scope->begin(); i != scope->end(); ++i) { untested();
    const COMPONENT* s = dynamic_cast<const COMPONENT*>(*i);
    if (!s){ untested();
    }else if (!s->is_device()){ untested();
    }else if (s->subckt()) { untested();
      _out << "-" << s->long_label() <<"\n";
      print(_out,s->subckt());
    }else{untested();
    }
  }
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class CMD_I : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM _out = IO::mstdout;
    _out.setfloatwidth(3);
    //_out.outset(cmd);
    _out << "listing i\n";
    if(_sim->_i){ untested();

    for ( uint_t i = 1;  CKT_BASE::_sim->_total_nodes + 1
        /* + CKT_BASE::_sim->_adp_nodes */
        > i ; ++i){ untested();
      _out << i;
      _out <<  CKT_BASE::_sim->_i[i] << "\n";
    }
    }else{ untested();
      _out<< " there are no currents\n";
    }
    //_out.outreset();
  }
} p7;
DISPATCHER<CMD>::INSTALL d7(&command_dispatcher, "ii", &p7);
/*--------------------------------------------------------------------------*/
class CMD_L : public CMD { //
public:
  void do_it(CS& cmd, CARD_LIST* )
  { untested();
    OMSTREAM _out = IO::mstdout;
    _out.setfloatwidth(3);
//    _out.outset(cmd);
    _out << OPT::language << "\n";
 //   _out.outreset();
  }
} p8;
DISPATCHER<CMD>::INSTALL d8(&command_dispatcher, "lang", &p8);
/*--------------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:et
