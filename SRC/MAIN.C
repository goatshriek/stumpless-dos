// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "stmplss.h"
#include <string.h>

/**
 * A CLI configuration.
 */
struct stmplss_config {
  bool stderr_enabled;
  bool stdout_enabled;
  bool file_enabled;
  bool default_enabled;
  const char *file_name;
  const char *message;
};

/**
 * Parses the provided command line arguments and populates a config instance
 * with the given settings.
 */
bool parse_args( int argc, char **argv, struct stmplss_config *config ){
  size_t i = 1;

  config->stderr_enabled = false;
  config->stdout_enabled = false;
  config->file_enabled = false;
  config->default_enabled = false;
  config->file_name = NULL;

  while( i < argc ){
    if( strcmp( argv[i], "-l" ) == 0
        || strcmp( argv[i], "--log-file" ) == 0 ){
      // filename arg
      i++;

      if( i >= argc ){
        // we need a filename!
        return false;
      }

      config->file_enabled = true;
      config->file_name = argv[i];
    } else if( strcmp( argv[i], "--stdout" ) == 0 ){
      config->stdout_enabled = true;
    } else if ( strcmp( argv[i], "--stderr" ) == 0 ){
      config->stderr_enabled = true;
    } else if( strcmp( argv[i], "--default" ) == 0 ){
      config->default_enabled = true;
    } else if( i + 1 == argc ) {
      config->message = argv[i];
      return true;
    } else {
      // unknown arg
      return false;
    }

    i++;
  }

  // no message!
  return false;
}

void print_usage( void ){
  puts( "Usage: STMPLSS.EXE [OPTIONS] message" );
  puts( "" );
  puts( "Arguments:" );
  puts( "  message The message to include in log messages." );
  puts( "" );
  puts( "Options:" );
  puts( "      --default          Log to the default log target. This is" );
  puts( "                         the default if no options are given." );
  puts( "  -l, --log-file <file>  Log to the given file." );
  puts( "      --stderr           Log to stderr." );
  puts( "      --stdout           Log to stdout." );
}

int main( int argc, char **argv ){
  struct stmplss_config config;
  struct stumpless_entry *entry;
  struct stumpless_target *file_target;
  struct stumpless_target *stderr_target;
  struct stumpless_target *stdout_target;
  struct stumpless_target *default_target;
  int log_result;
  bool default_needed;
  int exit_code = 0;

  if( !parse_args( argc, argv, &config ) ){
    print_usage();
    return -1;
  }

  entry = stumpless_new_entry_str( STUMPLESS_DEFAULT_FACILITY,
                                   STUMPLESS_DEFAULT_SEVERITY,
                                   argv[0],
                                   "stmplss",
                                   config.message );
  if( !entry ){
    stumpless_perror( "couldn't create an entry" );
    exit_code = -1;
    goto finish;
  }

  if( config.file_enabled ){
    file_target = stumpless_open_file_target( config.file_name );
    if( !file_target ){
      stumpless_perror( "opening the file target failed" );
      exit_code = -1;

    } else {
      log_result = stumpless_add_entry( file_target, entry );
      if( log_result < 0 ){
        stumpless_perror( "logging to the file target failed" );
        exit_code = -1;
      }

      stumpless_close_file_target( file_target );
    }
  }

  if( config.stderr_enabled ){
    stderr_target = stumpless_open_stderr_target( "stderr" );
    if( !stderr_target ){
      stumpless_perror( "opening the stderr target failed" );
      exit_code = -1;

    } else {
      log_result = stumpless_add_entry( stderr_target, entry );
      if( log_result < 0 ){
        stumpless_perror( "logging to the stderr target failed" );
        exit_code = -1;
      }

      stumpless_close_stream_target( stderr_target );
    }
  }

  if( config.stdout_enabled ){
    stdout_target = stumpless_open_stdout_target( "stdout" );
    if( !stdout_target ){
      stumpless_perror( "opening the stdout target failed" );
      exit_code = -1;

    } else {
      log_result = stumpless_add_entry( stdout_target, entry );
      if( log_result < 0 ){
        stumpless_perror( "logging to the stdout target failed" );
        exit_code = -1;
      }

      stumpless_close_stream_target( stdout_target );
    }
  }

  default_needed = !config.file_enabled
                   && !config.stdout_enabled
                   && !config.stderr_enabled;
  if( config.default_enabled || default_needed ){
    default_target = stumpless_get_default_target();
    if( !default_target ){
      stumpless_perror( "couldn't get the default target" );
      exit_code = -1;

    } else {
      log_result = stumpless_add_entry( default_target, entry );
      if( log_result < 0 ){
        stumpless_perror( "logging to the default target failed" );
        exit_code = -1;
      }
    }
  }

finish:
  stumpless_destroy_entry_and_contents( entry );
  stumpless_free_all();
  return exit_code;
}
