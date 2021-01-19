///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2021 CacheQ Systems Inc. All rights reserved.
//
// qemupost
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <vector>

#include "CLI11/CLI11x.hpp"


///////////////////////////////////////////////////////////////////////////////
//
// GLOBAL DEFINES:
//
///////////////////////////////////////////////////////////////////////////////

// TB element.
struct TB_element
    {
    uint32_t              start_address;
    uint32_t              end_address;
    uint32_t              instruction_count;
    std::vector<uint32_t> instructions;
    };
typedef struct TB_element TB_element;

// Full TB data set.
typedef std::map<int32_t, TB_element> TB_data_set;

// PC element.
struct PC_element
    {
    uint32_t              start_address;
    uint32_t              end_address;
    uint32_t              instruction_count;
    };
typedef PC_element PC_element;

// Full PC data set.
struct PC_data_set
    {
    uint32_t                next_PC_address;
    std::vector<PC_element> elements;
    };
typedef struct PC_data_set PC_data_set;


///////////////////////////////////////////////////////////////////////////////
//
// GLOBAL VARIABLES:
//
///////////////////////////////////////////////////////////////////////////////

// Global command line options.
bool debug_option;
bool verbose_option;

// Approximate percentage a timing value appears in PPC instructions.
const uint32_t timing_percent_table_size = 40;

uint32_t timing_percent_table[ timing_percent_table_size ] =
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 27.5%
      2, 2, 2, 2, 2, 2,                // 15.0%
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3,    // 25.0%
      4, 4, 4, 4,                      // 10.0%
      5,                               //  2.5%
      7, 7, 7, 7, 7, 7, 7,             // 17.5%
      8                                //  2.5%
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: dectohex8
//
///////////////////////////////////////////////////////////////////////////////

std::string
dectohex8( uint32_t value )
    {
    std::ostringstream ret;
    
    ret << "0x" << std::hex << std::setfill( '0' ) << std::setw( 8 ) << std::uppercase << value;
            
    return ret.str();
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: open_input_bin_stream
//
///////////////////////////////////////////////////////////////////////////////

inline std::ifstream
open_input_bin_stream( const std::string & bin_file_name )
    {
    std::ifstream binfile;
    
    binfile.open( bin_file_name,
                  std::ios::in | std::ios::binary );
    
    return binfile;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: open_output_bin_stream
//
///////////////////////////////////////////////////////////////////////////////

inline std::ofstream
open_output_bin_stream( const std::string & bin_file_name )
    {
    std::ofstream binfile;
    
    binfile.open( bin_file_name,
                  std::ios::out | std::ios::trunc | std::ios::binary );
    
    return binfile;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: read_stream_word
//
// Read 32 bit words as big endian.
//
///////////////////////////////////////////////////////////////////////////////

inline uint32_t
read_stream_word( std::ifstream & input_stream )
    {
    uint8_t  stream_bytes[ 4 ];
    uint32_t stream_word = 0;
    
    // Try reading the first byte of the next word.
    input_stream.read( (char *)&stream_bytes[ 0 ], 1 );
    
    // If we're not at EOF.
    if( input_stream )
        {
        // Read the rest of the bytes of a word....
        input_stream.read( (char *)&stream_bytes[ 1 ], 1 );
        input_stream.read( (char *)&stream_bytes[ 2 ], 1 );
        input_stream.read( (char *)&stream_bytes[ 3 ], 1 );
        
        // and return those bytes as a big endian data.
        stream_word = ( stream_bytes[ 0 ] << 24 ) | ( stream_bytes[ 1 ] << 16 ) | ( stream_bytes[ 2 ] << 8 ) | stream_bytes[ 3 ];
        }
    
    return stream_word;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: write_stream_word
//
// Write 32 bit words as big endian.
//
///////////////////////////////////////////////////////////////////////////////

inline void
write_stream_word( std::ofstream & output_stream,
                   uint32_t        stream_word )
    {
    uint8_t  stream_bytes[ 4 ];
    
    stream_bytes[ 0 ] = ( stream_word >> 24 ) & 0xFF;
    stream_bytes[ 1 ] = ( stream_word >> 16 ) & 0xFF;
    stream_bytes[ 2 ] = ( stream_word >> 8 ) & 0xFF;
    stream_bytes[ 3 ] = stream_word & 0xFF;
    
    output_stream.write( (char *)&stream_bytes[ 0 ], sizeof( stream_bytes ) );
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: open_bin_stream
//
///////////////////////////////////////////////////////////////////////////////

std::ifstream
open_bin_stream( const std::string & bin_file_name )
    {
    std::ifstream input_bin_stream = open_input_bin_stream( bin_file_name );
    uint32_t      stream_word;
    
    if( input_bin_stream )
        {
        
        // Check the header word to detect endianness.
        stream_word = read_stream_word( input_bin_stream );
        
        if( stream_word == 0x5A5AA5A5 )
            {
            
            // Check for format version 1.00.
            stream_word = read_stream_word( input_bin_stream );
            
            if( stream_word == 1000 )
                {
                }
            }
        }
    
    return input_bin_stream;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: read_next_TB
//
///////////////////////////////////////////////////////////////////////////////

TB_element
read_next_TB( std::ifstream & TB_stream )
    {
    TB_element next_tb_element;
    
    // Get starting TB address from the TB file.
    next_tb_element.start_address = read_stream_word( TB_stream );
    
    // If we're not at EOF.
    if( TB_stream )
        {
        // Get number of TB instructions.
        next_tb_element.instruction_count = read_stream_word( TB_stream );
        
        // Calculate ending address address.
        next_tb_element.end_address = next_tb_element.start_address + ( ( next_tb_element.instruction_count - 1 ) * sizeof( uint32_t ) );
        
        // Get the TB instructions.
        for( int instruction_count = next_tb_element.instruction_count; instruction_count > 0; --instruction_count )
            {
            uint32_t stream_word = read_stream_word( TB_stream );

            next_tb_element.instructions.push_back( stream_word );
            }
        }
    
    return next_tb_element;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: read_TB_data
//
///////////////////////////////////////////////////////////////////////////////

void
read_TB_data( const std::string & TB_bin_file_name,
              TB_data_set &       TB_data )
    {
    TB_element    next_tb_element;
    std::ifstream inputTBstream = open_bin_stream( TB_bin_file_name );
    
    // Try reading in the first TB.
    next_tb_element = read_next_TB( inputTBstream );
    
    // While there is still TB data to tbe read.
    while( inputTBstream )
        {
        // Add the current TB to the full TB data set.
        TB_data[ next_tb_element.start_address ] = next_tb_element;
        
        // Try reading in the next TB.
        next_tb_element = read_next_TB( inputTBstream );
        }
    
    inputTBstream.close();
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: read_next_PC
//
///////////////////////////////////////////////////////////////////////////////

PC_element
read_next_PC( std::ifstream & PC_stream )
    {
    PC_element next_pc_element;
    
    // Get starting PC address from the PC file.
    next_pc_element.start_address = read_stream_word( PC_stream );
    
    // If we're not at EOF.
    if( PC_stream )
        {
        // Get number of PC instructions.
        next_pc_element.instruction_count = read_stream_word( PC_stream );
        
        // Calculate ending address address.
        next_pc_element.end_address = next_pc_element.start_address + ( ( next_pc_element.instruction_count - 1 ) * sizeof( uint32_t ) );
        }
    
    return next_pc_element;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: read_PC_data
//
///////////////////////////////////////////////////////////////////////////////

void
read_PC_data( const std::string & PC_bin_file_name,
              PC_data_set &       PC_data )
    {
    PC_element    next_pc_element;
    std::ifstream inputPCstream = open_bin_stream( PC_bin_file_name );
    
    // Try reading in the first PC element.
    next_pc_element = read_next_PC( inputPCstream );
    
    // While there is still TB data to tbe read.
    while( inputPCstream )
        {
        // Add the current PC to the full PC data set.
        PC_data.elements.push_back( next_pc_element );
        
        // Try reading in the next PC.
        next_pc_element = read_next_PC( inputPCstream );
        }
    
    inputPCstream.close();
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_timing_value
//
// Simulate the approximate percentage that timing values appear in the set
// of PPC instructions.
//
// Use this function to generate pseudo-realistic timing values until the
// real Timing Value Lookup package is completed.
//
///////////////////////////////////////////////////////////////////////////////

uint8_t
lookup_timing_value( uint32_t ppc_instruction )
    {
    uint8_t timing_value;
    
    // Get an index limited to the size of the "timing_percent_table".
    timing_value = rand() % timing_percent_table_size;
    
    // Lookup a timing value from tthe "timing_percent_table".
    timing_value = timing_percent_table[ timing_value ];
    
    return timing_value;
    }


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: output_instruction_timing_values
//
///////////////////////////////////////////////////////////////////////////////

void
output_instruction_timing_values( const std::string & timing_bin_file_name,
                                  TB_data_set &       TB_data,
                                  PC_data_set &       PC_data )
    {
    std::ofstream output_bin_stream = open_output_bin_stream( timing_bin_file_name );
    
    // Loop through all of the PC execution records.
    for( auto pc_element : PC_data.elements )
        {
        uint32_t pc_instruction_address = pc_element.start_address;
        
        // Get the TB for the next PC execution record.
        TB_element tb_element = TB_data[ pc_instruction_address ];
        
        // Loop through the instruction in the TB.
        for( auto ppc_instruction : tb_element.instructions )
            {
            // Get the timing value for the next instruction.
            uint8_t pc_instruction_timing = lookup_timing_value( ppc_instruction );
            
            // Show the instruction at each execution address and its timing value.
            std::cout << dectohex8( pc_instruction_address )
                      << ":    "
                      << dectohex8( ppc_instruction )
                      << "   "
                      << std::to_string( pc_instruction_timing )
                      << std::endl;
            
            // Output the timing value to the Timing Value bin file.
            output_bin_stream.write( (char *)&pc_instruction_timing, 1 );
            
            // Go to the next instruction.
            pc_instruction_address += sizeof( uint32_t );
            }
        }
    
    output_bin_stream.close();
    }


///////////////////////////////////////////////////////////////////////////////
//
// CLASS: CLIx_Parse
//
///////////////////////////////////////////////////////////////////////////////

class CLIx_Parse
    {
    
    public:
    
    std::string code_file_name;
    std::string exec_file_name;
    std::string output_file_name;
    
    
    ///////////////////////////////////////////////////////////////////////////////
    //
    // METHOD: parse
    //
    ///////////////////////////////////////////////////////////////////////////////

    CLIx_Parse( int    argc,
                char * argv[] )
        {
        CLIx::App app_options( argc,
                               argv );
        
            
        app_options.description( "Post process QEMU timing profile data" );
        app_options.copyright( "Copyright (C) 2018-2021 by CacheQ, Inc." );
        
        auto option_infile = app_options.add_option( "-c,--codefile", code_file_name );
             option_infile->type_name( "<.bin filename>" );
             option_infile->description( "Input .bin TB code file." );
             option_infile->required();
        
        auto option_outfile = app_options.add_option( "-e,--execfile", exec_file_name );
             option_outfile->type_name( "<.bin filename>" );
             option_outfile->description( "Input .bin PC execution trace." );
        
        auto option_execfile = app_options.add_option( "-o,--output", output_file_name );
             option_execfile->type_name( "<.bin filename>" );
             option_execfile->description( "Output QEMU timing profile data file." );
        
        // Hidden debug output flag option.
        auto option_debug = app_options.add_flag( "-d", debug_option );
             option_debug->group("");
            
        // Hidden verbose output flag option.
        auto option_verbose = app_options.add_flag( "-v", verbose_option );
             option_verbose->group("");
        
        try
            {
            app_options.parse( argc,
                               argv);
            }
        catch( const CLI::ParseError &e )
            {
            std::cerr << "\nERROR -- qemupost - Command line option parse error.\n";
            
            exit( app_options.exit( e ) );
            }
        }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: main
//
///////////////////////////////////////////////////////////////////////////////

int
main( int    argc,
      char * argv[] )
    {
    TB_data_set TB_data;
    PC_data_set PC_data;
    
    CLIx_Parse cmd_options( argc,
                            argv );
    
    read_TB_data( cmd_options.code_file_name,
                  TB_data );
    
    read_PC_data( cmd_options.exec_file_name,
                  PC_data );
    
    output_instruction_timing_values( cmd_options.output_file_name,
                                      TB_data,
                                      PC_data );
    
    return 0;

// Test code.
#if 0
    for( auto pc_element : PC_data.elements )
        {
        std::cout << "start_address = " << dectohex8( pc_element.start_address ) << ", "
                  << "end_address = " << dectohex8( pc_element.end_address ) << ", "
                  << "instruction_count = " << dectohex8( pc_element.instruction_count ) << "."
                  << std::endl;
        
        TB_element tb_element = TB_data[ pc_element.start_address ];
        
        std::cout << "start_address = " << dectohex8( tb_element.start_address ) << ", "
                  << "end_address = " << dectohex8( tb_element.end_address ) << ", "
                  << "instruction_count = " << dectohex8( tb_element.instruction_count ) << "."
                  << std::endl;
        
        std::cout << std::endl;
        
//        if( TB_data.find( pc_element.start_address ) == TB_data.end() )
//            std::cout << "Not found!" << std::endl;
        }
#endif
    }
