/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Frederic Py.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the TREX Project nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef H_trex_python_python_env
# define H_trex_python_python_env

# include <trex/utils/LogManager.hh>
# include <trex/utils/priority_strand.hh>
# include <boost/python.hpp>
# include <map>

namespace TREX {
  namespace python {
    
    class python_env :boost::noncopyable {
    public:
      boost::python::object &import(std::string const &module);
      boost::python::object load_module_for(std::string const &type);
      boost::python::object add_module(boost::python::object scope, std::string const &name);
      
      boost::python::object dir(boost::python::object const &obj) const;
      bool callable(boost::python::object const &obj) const;
      bool is_instance(boost::python::object const &obj,
                       boost::python::object const &type) const;

      boost::python::object main() const {
        return m_main;
      }
      boost::python::dict main_env() const;
      
      utils::priority_strand &strand() {
        return m_strand;
      }
      
    private:
      typedef std::map<std::string, boost::python::object> object_map;
      object_map m_loaded;
      boost::python::object m_main;
      
      
      python_env();
      ~python_env();
      
      utils::SingletonUse<utils::LogManager> m_log;
      utils::priority_strand m_strand;

      friend class TREX::utils::SingletonWrapper<python_env>;
    };
    
  }
}


#endif // H_trex_python_python_env
