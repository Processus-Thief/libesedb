/*
 * Windows search compression functions test program
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "esedb_test_libcerror.h"
#include "esedb_test_macros.h"
#include "esedb_test_memory.h"
#include "esedb_test_unused.h"

#include "../esedbtools/windows_search_compression.h"

uint8_t esedb_test_tools_windows_search_utf16_run_length_compressed_data[ 725 ] = {
	0xff, 0x00, 0x23, 0x4d, 0x33, 0x55, 0x0d, 0x0a, 0x28, 0x30, 0x31, 0x29, 0x20, 0x5b, 0x42, 0x4b,
	0x61, 0x6d, 0x75, 0x69, 0x5d, 0x20, 0x45, 0x78, 0x63, 0x65, 0x65, 0x64, 0x2e, 0x6d, 0x70, 0x33,
	0x0d, 0x0a, 0x28, 0x30, 0x32, 0x29, 0x20, 0x5b, 0x4c, 0x69, 0x73, 0x61, 0x20, 0x4c, 0x61, 0x73,
	0x68, 0x65, 0x73, 0x5d, 0x20, 0x4d, 0x61, 0x78, 0x77, 0x65, 0x6c, 0x6c, 0x2e, 0x6d, 0x70, 0x33,
	0x0d, 0x0a, 0x28, 0x30, 0x33, 0x29, 0x20, 0x5b, 0x45, 0x76, 0x61, 0x6e, 0x74, 0x69, 0x5d, 0x20,
	0x57, 0x68, 0x61, 0x74, 0x20, 0x59, 0x6f, 0x75, 0x20, 0x53, 0x65, 0x65, 0x20, 0x49, 0x73, 0x20,
	0x57, 0x68, 0x61, 0x74, 0x20, 0x59, 0x6f, 0x75, 0x20, 0x57, 0x61, 0x6e, 0x74, 0x2e, 0x6d, 0x70,
	0x33, 0x0d, 0x0a, 0x28, 0x30, 0x34, 0x29, 0x20, 0x5b, 0x4c, 0x75, 0x6e, 0x61, 0x5d, 0x20, 0x55,
	0x6e, 0x6c, 0x6f, 0x63, 0x6b, 0x65, 0x64, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x30, 0x35,
	0x29, 0x20, 0x5b, 0x52, 0x75, 0x74, 0x68, 0x6c, 0x65, 0x73, 0x73, 0x5d, 0x20, 0x47, 0x65, 0x72,
	0x73, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x30, 0x36, 0x29, 0x20, 0x5b, 0x53, 0x61, 0x6d,
	0x75, 0x61, 0x6c, 0x20, 0x53, 0x61, 0x6e, 0x64, 0x65, 0x72, 0x73, 0x5d, 0x20, 0x41, 0x78, 0x69,
	0x73, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x30, 0x37, 0x29, 0x20, 0x5b, 0x42, 0x65, 0x61,
	0x74, 0x20, 0x50, 0x72, 0x6f, 0x76, 0x69, 0x64, 0x65, 0x72, 0x73, 0x5d, 0x20, 0x4e, 0x65, 0x61,
	0x72, 0x20, 0x44, 0x65, 0x61, 0x74, 0x68, 0x20, 0x45, 0x78, 0x70, 0x65, 0x72, 0x69, 0x65, 0x6e,
	0x63, 0x65, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x30, 0x38, 0x29, 0x20, 0x5b, 0x44, 0x61,
	0x69, 0x68, 0x00, 0x6c, 0x75, 0x63, 0x69, 0x61, 0x5d, 0x20, 0x4d, 0x75, 0x73, 0x69, 0x63, 0x20,
	0x4f, 0x76, 0x65, 0x72, 0x20, 0x4d, 0x69, 0x6e, 0x64, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28,
	0x30, 0x39, 0x29, 0x20, 0x5b, 0x41, 0x2d, 0x4c, 0x75, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x6d, 0x65,
	0x65, 0x74, 0x73, 0x20, 0x53, 0x63, 0x6f, 0x70, 0x65, 0x20, 0x44, 0x4a, 0x5d, 0x20, 0x42, 0x65,
	0x74, 0x77, 0x65, 0x65, 0x6e, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x73, 0x2e, 0x6d, 0x70, 0x33,
	0x0d, 0x0a, 0x28, 0x31, 0x30, 0x29, 0x20, 0x5b, 0x54, 0x61, 0x74, 0x61, 0x6e, 0x6b, 0x61, 0x20,
	0x50, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x5d, 0x20, 0x44, 0x4a, 0x01, 0x20, 0x19, 0xff, 0x00,
	0x73, 0x20, 0x4c, 0x69, 0x66, 0x65, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x31, 0x31, 0x29,
	0x20, 0x5b, 0x50, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x20, 0x31, 0x5d, 0x20, 0x4e, 0x75, 0x6d,
	0x62, 0x65, 0x72, 0x73, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x31, 0x32, 0x29, 0x20, 0x5b,
	0x54, 0x65, 0x63, 0x68, 0x6e, 0x6f, 0x62, 0x6f, 0x79, 0x5d, 0x20, 0x50, 0x75, 0x74, 0x20, 0x53,
	0x6f, 0x6d, 0x65, 0x20, 0x47, 0x72, 0x61, 0x63, 0x65, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28,
	0x31, 0x33, 0x29, 0x20, 0x5b, 0x4e, 0x61, 0x6b, 0x65, 0x64, 0x20, 0x53, 0x74, 0x65, 0x65, 0x6c,
	0x5d, 0x20, 0x56, 0x69, 0x76, 0x65, 0x20, 0x4c, 0x61, 0x20, 0x46, 0x72, 0x61, 0x6e, 0x63, 0x65,
	0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28, 0x31, 0x34, 0x29, 0x20, 0x5b, 0x43, 0x68, 0x61, 0x72,
	0x6c, 0x79, 0x20, 0x4c, 0x6f, 0x77, 0x6e, 0x6f, 0x69, 0x73, 0x65, 0x20, 0x26, 0x20, 0x4d, 0x65,
	0x6e, 0x74, 0x61, 0x6c, 0x20, 0x54, 0x68, 0x65, 0x6f, 0x5d, 0x20, 0x57, 0x6f, 0x6e, 0x64, 0x65,
	0x72, 0x66, 0x75, 0x6c, 0x20, 0x44, 0x61, 0x79, 0x73, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28,
	0x31, 0x35, 0x29, 0x20, 0x5b, 0x54, 0x6f, 0x6d, 0x6d, 0x79, 0x6b, 0x6e, 0x6f, 0x63, 0x6b, 0x65,
	0x72, 0x5d, 0x20, 0x43, 0x72, 0x75, 0x6e, 0x63, 0x68, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28,
	0x31, 0x36, 0x29, 0x20, 0x5b, 0x45, 0x76, 0x69, 0x6c, 0x20, 0x41, 0x63, 0x74, 0x69, 0x76, 0x69,
	0x74, 0x69, 0x74, 0x65, 0x73, 0x20, 0x26, 0x20, 0x50, 0x61, 0x6e, 0x69, 0x63, 0x20, 0x46, 0x65,
	0x61, 0x74, 0x2e, 0x20, 0x4d, 0x43, 0x20, 0x41, 0x6c, 0x65, 0x65, 0x5d, 0x20, 0x49, 0x6e, 0x31,
	0x00, 0x76, 0x69, 0x6e, 0x63, 0x69, 0x62, 0x6c, 0x65, 0x2e, 0x6d, 0x70, 0x33, 0x0d, 0x0a, 0x28,
	0x31, 0x37, 0x29, 0x20, 0x5b, 0x54, 0x68, 0x65, 0x20, 0x4f, 0x75, 0x74, 0x73, 0x69, 0x64, 0x65,
	0x20, 0x41, 0x6e, 0x67, 0x65, 0x6e, 0x63, 0x79, 0x5d, 0x20, 0x53, 0x74, 0x72, 0x61, 0x6e, 0x67,
	0x65, 0x72, 0x01, 0x20, 0x19, 0x2e, 0x00, 0x73, 0x20, 0x43, 0x61, 0x6c, 0x6c, 0x2e, 0x6d, 0x70,
	0x33, 0x0d, 0x0a, 0x28, 0x31, 0x38, 0x29, 0x20, 0x5b, 0x45, 0x6e, 0x7a, 0x79, 0x6d, 0x65, 0x20,
	0x58, 0x5d, 0x20, 0x53, 0x69, 0x6c, 0x6c, 0x79, 0x20, 0x4d, 0x69, 0x64, 0x20, 0x4f, 0x6e, 0x2e,
	0x6d, 0x70, 0x33, 0x0d, 0x0a };

uint8_t esedb_test_tools_windows_search_utf16_run_length_uncompressed_data[ 1422 ] = {
	0x23, 0x00, 0x4d, 0x00, 0x33, 0x00, 0x55, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00,
	0x31, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x42, 0x00, 0x4b, 0x00, 0x61, 0x00, 0x6d, 0x00,
	0x75, 0x00, 0x69, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x45, 0x00, 0x78, 0x00, 0x63, 0x00, 0x65, 0x00,
	0x65, 0x00, 0x64, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00,
	0x28, 0x00, 0x30, 0x00, 0x32, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x4c, 0x00, 0x69, 0x00,
	0x73, 0x00, 0x61, 0x00, 0x20, 0x00, 0x4c, 0x00, 0x61, 0x00, 0x73, 0x00, 0x68, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x61, 0x00, 0x78, 0x00, 0x77, 0x00, 0x65, 0x00,
	0x6c, 0x00, 0x6c, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00,
	0x28, 0x00, 0x30, 0x00, 0x33, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x45, 0x00, 0x76, 0x00,
	0x61, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x69, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x57, 0x00, 0x68, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x20, 0x00, 0x59, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x20, 0x00, 0x53, 0x00,
	0x65, 0x00, 0x65, 0x00, 0x20, 0x00, 0x49, 0x00, 0x73, 0x00, 0x20, 0x00, 0x57, 0x00, 0x68, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x20, 0x00, 0x59, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x20, 0x00, 0x57, 0x00,
	0x61, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00,
	0x0a, 0x00, 0x28, 0x00, 0x30, 0x00, 0x34, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x4c, 0x00,
	0x75, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x55, 0x00, 0x6e, 0x00, 0x6c, 0x00,
	0x6f, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x65, 0x00, 0x64, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00,
	0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00, 0x35, 0x00, 0x29, 0x00, 0x20, 0x00,
	0x5b, 0x00, 0x52, 0x00, 0x75, 0x00, 0x74, 0x00, 0x68, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x73, 0x00,
	0x73, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x47, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x2e, 0x00,
	0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00, 0x36, 0x00,
	0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x53, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x75, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x20, 0x00, 0x53, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x73, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x41, 0x00, 0x78, 0x00, 0x69, 0x00, 0x73, 0x00, 0x2e, 0x00,
	0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00, 0x37, 0x00,
	0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x42, 0x00, 0x65, 0x00, 0x61, 0x00, 0x74, 0x00, 0x20, 0x00,
	0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x76, 0x00, 0x69, 0x00, 0x64, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x73, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x4e, 0x00, 0x65, 0x00, 0x61, 0x00, 0x72, 0x00, 0x20, 0x00,
	0x44, 0x00, 0x65, 0x00, 0x61, 0x00, 0x74, 0x00, 0x68, 0x00, 0x20, 0x00, 0x45, 0x00, 0x78, 0x00,
	0x70, 0x00, 0x65, 0x00, 0x72, 0x00, 0x69, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x63, 0x00, 0x65, 0x00,
	0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00,
	0x38, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x44, 0x00, 0x61, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x75, 0x00, 0x63, 0x00, 0x69, 0x00, 0x61, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x75, 0x00,
	0x73, 0x00, 0x69, 0x00, 0x63, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x76, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x20, 0x00, 0x4d, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00,
	0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x30, 0x00, 0x39, 0x00, 0x29, 0x00, 0x20, 0x00,
	0x5b, 0x00, 0x41, 0x00, 0x2d, 0x00, 0x4c, 0x00, 0x75, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x20, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x65, 0x00, 0x74, 0x00, 0x73, 0x00, 0x20, 0x00,
	0x53, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x70, 0x00, 0x65, 0x00, 0x20, 0x00, 0x44, 0x00, 0x4a, 0x00,
	0x5d, 0x00, 0x20, 0x00, 0x42, 0x00, 0x65, 0x00, 0x74, 0x00, 0x77, 0x00, 0x65, 0x00, 0x65, 0x00,
	0x6e, 0x00, 0x20, 0x00, 0x57, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x6c, 0x00, 0x64, 0x00, 0x73, 0x00,
	0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00,
	0x30, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x54, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00,
	0x6e, 0x00, 0x6b, 0x00, 0x61, 0x00, 0x20, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x6a, 0x00,
	0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x44, 0x00, 0x4a, 0x00, 0x19, 0x20,
	0x73, 0x00, 0x20, 0x00, 0x4c, 0x00, 0x69, 0x00, 0x66, 0x00, 0x65, 0x00, 0x2e, 0x00, 0x6d, 0x00,
	0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00, 0x31, 0x00, 0x29, 0x00,
	0x20, 0x00, 0x5b, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x6a, 0x00, 0x65, 0x00, 0x63, 0x00,
	0x74, 0x00, 0x20, 0x00, 0x31, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x4e, 0x00, 0x75, 0x00, 0x6d, 0x00,
	0x62, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00,
	0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00, 0x32, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00,
	0x54, 0x00, 0x65, 0x00, 0x63, 0x00, 0x68, 0x00, 0x6e, 0x00, 0x6f, 0x00, 0x62, 0x00, 0x6f, 0x00,
	0x79, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x50, 0x00, 0x75, 0x00, 0x74, 0x00, 0x20, 0x00, 0x53, 0x00,
	0x6f, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x20, 0x00, 0x47, 0x00, 0x72, 0x00, 0x61, 0x00, 0x63, 0x00,
	0x65, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00,
	0x31, 0x00, 0x33, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6b, 0x00,
	0x65, 0x00, 0x64, 0x00, 0x20, 0x00, 0x53, 0x00, 0x74, 0x00, 0x65, 0x00, 0x65, 0x00, 0x6c, 0x00,
	0x5d, 0x00, 0x20, 0x00, 0x56, 0x00, 0x69, 0x00, 0x76, 0x00, 0x65, 0x00, 0x20, 0x00, 0x4c, 0x00,
	0x61, 0x00, 0x20, 0x00, 0x46, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x63, 0x00, 0x65, 0x00,
	0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00,
	0x34, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x43, 0x00, 0x68, 0x00, 0x61, 0x00, 0x72, 0x00,
	0x6c, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4c, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x6e, 0x00, 0x6f, 0x00,
	0x69, 0x00, 0x73, 0x00, 0x65, 0x00, 0x20, 0x00, 0x26, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x65, 0x00,
	0x6e, 0x00, 0x74, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x20, 0x00, 0x54, 0x00, 0x68, 0x00, 0x65, 0x00,
	0x6f, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x57, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x66, 0x00, 0x75, 0x00, 0x6c, 0x00, 0x20, 0x00, 0x44, 0x00, 0x61, 0x00, 0x79, 0x00,
	0x73, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00,
	0x31, 0x00, 0x35, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x54, 0x00, 0x6f, 0x00, 0x6d, 0x00,
	0x6d, 0x00, 0x79, 0x00, 0x6b, 0x00, 0x6e, 0x00, 0x6f, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x43, 0x00, 0x72, 0x00, 0x75, 0x00, 0x6e, 0x00, 0x63, 0x00,
	0x68, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00,
	0x31, 0x00, 0x36, 0x00, 0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x45, 0x00, 0x76, 0x00, 0x69, 0x00,
	0x6c, 0x00, 0x20, 0x00, 0x41, 0x00, 0x63, 0x00, 0x74, 0x00, 0x69, 0x00, 0x76, 0x00, 0x69, 0x00,
	0x74, 0x00, 0x69, 0x00, 0x74, 0x00, 0x65, 0x00, 0x73, 0x00, 0x20, 0x00, 0x26, 0x00, 0x20, 0x00,
	0x50, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x69, 0x00, 0x63, 0x00, 0x20, 0x00, 0x46, 0x00, 0x65, 0x00,
	0x61, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x43, 0x00, 0x20, 0x00, 0x41, 0x00,
	0x6c, 0x00, 0x65, 0x00, 0x65, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x76, 0x00,
	0x69, 0x00, 0x6e, 0x00, 0x63, 0x00, 0x69, 0x00, 0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x2e, 0x00,
	0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00, 0x37, 0x00,
	0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x54, 0x00, 0x68, 0x00, 0x65, 0x00, 0x20, 0x00, 0x4f, 0x00,
	0x75, 0x00, 0x74, 0x00, 0x73, 0x00, 0x69, 0x00, 0x64, 0x00, 0x65, 0x00, 0x20, 0x00, 0x41, 0x00,
	0x6e, 0x00, 0x67, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x63, 0x00, 0x79, 0x00, 0x5d, 0x00, 0x20, 0x00,
	0x53, 0x00, 0x74, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x19, 0x20, 0x73, 0x00, 0x20, 0x00, 0x43, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x2e, 0x00,
	0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00, 0x28, 0x00, 0x31, 0x00, 0x38, 0x00,
	0x29, 0x00, 0x20, 0x00, 0x5b, 0x00, 0x45, 0x00, 0x6e, 0x00, 0x7a, 0x00, 0x79, 0x00, 0x6d, 0x00,
	0x65, 0x00, 0x20, 0x00, 0x58, 0x00, 0x5d, 0x00, 0x20, 0x00, 0x53, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x6c, 0x00, 0x79, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x69, 0x00, 0x64, 0x00, 0x20, 0x00, 0x4f, 0x00,
	0x6e, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x33, 0x00, 0x0d, 0x00, 0x0a, 0x00 };

/* Tests the windows_search_utf16_run_length_compression_get_size function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_tools_windows_search_utf16_run_length_compression_get_size(
     void )
{
	libcerror_error_t *error      = NULL;
	size_t uncompressed_data_size = 0;
	int result                    = 0;

	/* Test regular cases
	 */
	result = windows_search_utf16_run_length_compression_get_size(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ESEDB_TEST_ASSERT_EQUAL_SIZE(
	 "uncompressed_data_size",
	 uncompressed_data_size,
	 (size_t) 1422 );

	ESEDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = windows_search_utf16_run_length_compression_get_size(
	          NULL,
	          725,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_get_size(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          (size_t) SSIZE_MAX + 1,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_get_size(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          0,
	          &uncompressed_data_size,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_get_size(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          NULL,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the windows_search_utf16_run_length_compression_decompress function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_tools_windows_search_utf16_run_length_compression_decompress(
     void )
{
	uint8_t uncompressed_data[ 2048 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          uncompressed_data,
	          1422,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ESEDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          uncompressed_data,
	          esedb_test_tools_windows_search_utf16_run_length_uncompressed_data,
	          1422 );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = windows_search_utf16_run_length_compression_decompress(
	          NULL,
	          725,
	          uncompressed_data,
	          1422,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          (size_t) SSIZE_MAX + 1,
	          uncompressed_data,
	          1422,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          0,
	          uncompressed_data,
	          1422,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          NULL,
	          1422,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          uncompressed_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = windows_search_utf16_run_length_compression_decompress(
	          esedb_test_tools_windows_search_utf16_run_length_compressed_data,
	          725,
	          uncompressed_data,
	          4,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ESEDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc ESEDB_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] ESEDB_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc ESEDB_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] ESEDB_TEST_ATTRIBUTE_UNUSED )
#endif
{
	ESEDB_TEST_UNREFERENCED_PARAMETER( argc )
	ESEDB_TEST_UNREFERENCED_PARAMETER( argv )

	ESEDB_TEST_RUN(
	 "windows_search_utf16_run_length_compression_get_size",
	 esedb_test_tools_windows_search_utf16_run_length_compression_get_size );

	ESEDB_TEST_RUN(
	 "windows_search_utf16_run_length_compression_decompress",
	 esedb_test_tools_windows_search_utf16_run_length_compression_decompress );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

