///////////////////////////////////////////////////////////////////////////////
//
// CLI11x: Version 1.0
// Written by Matthew Nelson
//
// This is a specilization of the CLI11 command line parser to have the
// "help" output look more Linux like and be easier to read.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CLI11.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// NAMESPACE: CLIx
//
///////////////////////////////////////////////////////////////////////////////

namespace CLIx
    {
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    // CLASS: formatter
    //
    ///////////////////////////////////////////////////////////////////////////////
    
    class Formatter : public CLI::Formatter
        {
        public:
            Formatter() : CLI::Formatter() {}
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_usage
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string make_usage( const CLI::App * app,
                                    std::string      name ) const override
                {
                std::stringstream out;

                out << "\n" << bold( get_label( "Usage" ) ) << "\n    " <<  ( name.empty() ? "" : " " ) << bold( name );

                std::vector<std::string> groups = app->get_groups();

                // Print an Options badge if any options exist
                std::vector<const CLI::Option *> non_pos_options =
                    app->get_options( [](const CLI::Option *opt ) { return opt->nonpositional(); } );
                
                if( !non_pos_options.empty() )
                    out << " [" << get_label( "OPTIONS" ) << "]";

                // Positionals need to be listed here
                std::vector<const CLI::Option *> positionals = app->get_options( [](const CLI::Option *opt ) { return opt->get_positional(); } );

                // Print out positionals if any are left
                if( !positionals.empty() )
                    {
                    // Convert to help names
                    std::vector<std::string> positional_names( positionals.size() );
                    std::transform( positionals.begin(), positionals.end(), positional_names.begin(), [ this ]( const CLI::Option *opt )
                                    {
                                    return make_option_usage( opt );
                                    }
                                   );

                    out << " " << CLI::detail::join( positional_names, " " );
                    }

                // Add a marker if subcommands are expected or optional
                if( !app->get_subcommands( {} ).empty() )
                    {
                    out << " " << ( app->get_require_subcommand_min() == 0 ? "[" : "" )
                        << get_label( ( app->get_require_subcommand_max() < 2 ) || ( app->get_require_subcommand_min() > 1 )
                                      ? "SUBCOMMAND"
                                      : "SUBCOMMANDS" )
                        << ( app->get_require_subcommand_min() == 0 ? "]" : "" );
                    }

                out << std::endl;

                return out.str();
                }
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_help
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string
            make_help( const CLI::App *   app,
                       std::string        name,
                       CLI::AppFormatMode mode ) const override
                {

                // This immediately forwards to the make_expanded method. This is done this way so that subcommands can
                // have overridden formatters
                if( mode == CLI::AppFormatMode::Sub )
                    return make_expanded( app );

                std::stringstream out;

                out << make_description( app );
                out << make_usage( app, name );
                out << make_copyright( app );
                out << make_positionals( app );
                out << make_groups( app, mode );
                out << make_subcommands( app, mode );
                out << make_footer( app );

                return out.str();
                }
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_description
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string make_description( const CLI::App * app ) const override
                {
                std::stringstream out;
                std::string       desc = app->get_description();
                
                out << "";
                
                if( !desc.empty() )
                    out << "\n" << bold( get_label( "NAME" ) ) << "\n    " << bold( app->get_name() ) << " -- " << desc << "\n";
                
                return out.str();
                }
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_copyright
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string make_copyright( const CLI::App * app ) const
                {
                std::stringstream out;
                std::string       copyright = get_copyright();
                
                out << "";
                
                if( !copyright.empty() )
                    out << "\n" << bold( get_label( "COPYRIGHT" ) ) << "\n    " << bold( app->get_name() ) << " is " << copyright << "\n";
                
                return out.str();
                }
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_option
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string make_option( const CLI::Option * opt,
                                     bool                is_positional ) const override
                {
                std::stringstream out;
                std::string       name = make_option_name( opt, is_positional ) + make_option_opts( opt );
                std::string       description = make_option_desc( opt );
                
                // Split up the option names so that we can have them
                // on separate lines.
                std::vector<std::string> opt_names =
                    CLI::detail::split( name, ',' );
                
                out << "\n";
                
                for( const auto & opt_name : opt_names )
                    {
                    std::vector<std::string> opt_specs =
                        CLI::detail::split( opt_name, ' ' );
                    
                    auto opt_specs_iter = opt_specs.begin();
                    out << "    " << bold( *opt_specs_iter );
                    ++opt_specs_iter;
                    
                    for( ; opt_specs_iter != opt_specs.end(); opt_specs_iter++ )
                        {
                        out << " " << *opt_specs_iter;
                        }
                    
                    out << "\n";
                    }
                
                if( !description.empty() )
                    out << "            " << description << "\n";
                
                return out.str();
                }
            
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: make_group
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            std::string
            make_group( std::string                      group,
                        bool                             is_positional,
                        std::vector<const CLI::Option *> opts ) const override
                {
                std::stringstream out;
                
                out << "\n" << bold( get_label( group ) ) << "\n";
                
                for( const CLI::Option * opt : opts )
                    {
                    out << make_option( opt,
                                        is_positional );
                    }
                
                return out.str();
                }
            
            /// Set a name for the app (empty will use parser to set the name)
            void
            copyright( std::string str = "" )
                {
                copyright_ = str;
                }
            
            std::string
            get_copyright() const
                {
                return copyright_;
                }
        
        protected:
            
            ///////////////////////////////////////////////////////////////////////////////
            //
            // METHOD: bold
            //
            ///////////////////////////////////////////////////////////////////////////////
            
            inline
            std::string
            bold( std::string str ) const
                {
#ifdef _WIN32
                // This doesn't work on Windows.
                return str;
#else
                return "\e[1m" + str + "\e[m";
#endif
                }

            // Copyright to be added the help out.
            std::string copyright_;
        };

    ///////////////////////////////////////////////////////////////////////////////
    //
    // CLASS: App
    //
    ///////////////////////////////////////////////////////////////////////////////

    class App : public CLI::App
        {
        // This library follows the Google style guide for member names ending in underscores
        public:
            
            App( int         argc,
                 char *      argv[],
                 std::string description = "",
                 std::string copyrightstr = "" )
                    : CLI::App( description )
                {
                // Trim the execution path off of the program name.
                std::string argv_app_name = argv[ 0 ];
                std::string argv_base_app_name = argv_app_name.substr( argv_app_name.find_last_of( "/\\" ) + 1 );
                
                name( argv_base_app_name );
                set_help_flag( "-h,--help", "Print this help message and exit." );
                fmt = std::make_shared<CLIx::Formatter>();
                formatter( fmt );
                fmt->label( "REQUIRED", "(Required)" );
                fmt->label( "OPTIONS", "options" );
                fmt->label( "Options", "OPTIONS" );
                fmt->label( "Usage", "SYNOPSIS" );
                
                copyright( copyrightstr );
                }
        
        /// Set a copyright string.
        void
        copyright( std::string str = "" )
            {
            fmt->copyright( str );
            }
        
        protected:
        
        /// This is the formatter for help printing.
        std::shared_ptr<CLIx::Formatter> fmt;
        };
    } // namespace CLIx
