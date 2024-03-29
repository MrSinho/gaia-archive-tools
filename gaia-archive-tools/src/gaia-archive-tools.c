#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

#include "gaia-archive-tools/gaiaArchiveTools.h"
#include "csv-fast-reader/csv.h"

#ifdef _MSC_VER
#pragma warning (disable: 4996)
#endif//_MSC_VER

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <inttypes.h>



uint8_t gaiaUniverseModelGetId(
	uint32_t id, 
	char*    s_dst
) {
	gaiaToolsError(s_dst == NULL, "invalid destination memory", return 0);

	strcpy(s_dst, "0000");
	if (id >= 1000) {
		sprintf(s_dst, "%" PRIu32, id);
	}
	else if (100 <= id && id < 1000) {
		sprintf(&s_dst[1], "%" PRIu32, id);
	}
	else if (10 <= id && id < 100) {
		sprintf(&s_dst[2], "%" PRIu32, id);
	}
	else if (id < 10) {
		sprintf(&s_dst[3], "%" PRIu32, id);
	}

	return 1;
}

uint32_t gaiaGetBodySize(
	GaiaCelestialBodyFlags flags
) {

	uint32_t src_size = 0;
	if (flags == GAIA_FULL_BODY)               { return GAIA_CELESTIAL_BODY_MAX_SIZE; }
	if (flags & GAIA_SOURCE_EXTENDED_ID)       { src_size += GAIA_SOURCE_EXTENDED_ID_SIZE; }
	if (flags & GAIA_SOURCE_ID)                { src_size += 8; }
	if (flags & GAIA_SOLUTION_ID)              { src_size += 8; }
	if (flags & GAIA_RA)                       { src_size += sizeof(gaia_real); }
	if (flags & GAIA_DEC)                      { src_size += sizeof(gaia_real); }
	if (flags & GAIA_BARYCENTRIC_DISTANCE)     { src_size += 4; }
	if (flags & GAIA_PMRA)                     { src_size += 4; }
	if (flags & GAIA_PMDEC)                    { src_size += 4; }
	if (flags & GAIA_RADIAL_VELOCITY)          { src_size += 4; }
	if (flags & GAIA_MAG_G)                    { src_size += 4; }
	if (flags & GAIA_MAG_BP)                   { src_size += 4; }
	if (flags & GAIA_MAG_RP)                   { src_size += 4; }
	if (flags & GAIA_MAG_RVS)                  { src_size += 4; }
	if (flags & GAIA_V_I)                      { src_size += 4; }
	if (flags & GAIA_MEAN_ABSOLUTE_V)          { src_size += 4; }
	if (flags & GAIA_AG)                       { src_size += 4; }
	if (flags & GAIA_AV)                       { src_size += 4; }
	if (flags & GAIA_TEFF)                     { src_size += 4; }
	if (flags & GAIA_LOGG)                     { src_size += 4; }
	if (flags & GAIA_FEH)                      { src_size += 4; }
	if (flags & GAIA_ALPHAFE)                  { src_size += 4; }
	if (flags & GAIA_MBOL)                     { src_size += 4; }
	if (flags & GAIA_AGE)                      { src_size += 4; }
	if (flags & GAIA_MASS)                     { src_size += 4; }
	if (flags & GAIA_RADIUS)                   { src_size += 4; }
	if (flags & GAIA_VSINI)                    { src_size += 4; }
	if (flags & GAIA_POPULATION)               { src_size += 1; }
	if (flags & GAIA_HAS_PHOTOCENTER_MOTION)   { src_size += 1; }
	if (flags & GAIA_NC)                       { src_size += 4; }
	if (flags & GAIA_NT)                       { src_size += 4; }
	if (flags & GAIA_SEMIMAJOR_AXIS)           { src_size += 4; }
	if (flags & GAIA_ECCENTRICITY)             { src_size += 4; }
	if (flags & GAIA_INCLINATION)              { src_size += 4; }
	if (flags & GAIA_LONGITUDE_ASCENDING_NODE) { src_size += 4; }
	if (flags & GAIA_ORBIT_PERIOD)             { src_size += 4; }
	if (flags & GAIA_PERIASTRON_DATE)          { src_size += 4; }
	if (flags & GAIA_PERIASTRON_ARGUMENT)      { src_size += 4; }
	if (flags & GAIA_VARIABILITY_AMPLITUDE)    { src_size += 4; }
	if (flags & GAIA_VARIABILITY_PERIOD)       { src_size += 4; }
	if (flags & GAIA_VARIABILITY_PHASE)        { src_size += 4; }

	return src_size;
}

uint8_t gaiaWriteByte(
    uint8_t   val, 
    uint32_t* p_dst_offset, 
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",     return 0);
	gaiaToolsError(p_dst        == NULL, "invalid dst buffer memory", return 0);

	memset(&((uint8_t*)p_dst)[*p_dst_offset], val, 1);
	(*p_dst_offset)++;

	return 1;
}

uint8_t gaiaWriteBuffer(
    void*     src, 
    uint32_t  size,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",     return 0);
	gaiaToolsError(p_dst        == NULL, "invalid dst buffer memory", return 0);

	memcpy((void*)(&((char*)p_dst)[*p_dst_offset]), src, size);
	(*p_dst_offset) += size;

	return 1;
}

uint8_t gaiaWriteLong(
    uint64_t  val,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",             return 0);
	gaiaToolsError(p_dst        == NULL, "invalid destination buffer memory", return 0);

	const uint64_t _val = val;
	gaiaWriteBuffer((void*)&_val, 8, p_dst_offset, p_dst);

	return 1;
}

uint8_t gaiaWriteDouble(
    double    val,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",             return 0);
	gaiaToolsError(p_dst        == NULL, "invalid destination buffer memory", return 0);

	const double _val = val;
	gaiaWriteBuffer((void*)&_val, 8, p_dst_offset, p_dst);

	return 1;
}

uint8_t gaiaWriteFloat(
    float     val,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",             return 0);
	gaiaToolsError(p_dst        == NULL, "invalid destination buffer memory", return 0);

	const float _val = val;
	gaiaWriteBuffer((void*)&_val, 4, p_dst_offset, p_dst);

	return 1;
}

uint8_t gaiaWriteBoolean(
    char*     src,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",             return 0);
	gaiaToolsError(p_dst        == NULL, "invalid destination buffer memory", return 0);

	if (strcmp(src, "True") == 0) {
		gaiaWriteByte(1, p_dst_offset, p_dst);
	}
	else {
		gaiaWriteByte(0, p_dst_offset, p_dst);
	}

	return 1;
}

uint8_t gaiaWriteInt(
    uint32_t  val,
    uint32_t* p_dst_offset,
    void*     p_dst
) {
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",             return 0);
	gaiaToolsError(p_dst        == NULL, "invalid destination buffer memory", return 0);

	const uint32_t _val = val;
	gaiaWriteBuffer((void*)&_val, 4, p_dst_offset, p_dst);

	return 1;
}

uint8_t gaiaReadBuffer(
    void*     p_dst, 
    uint32_t  size, 
    uint32_t  src_offset, 
    uint32_t* p_dst_offset,
    void*     p_src
) {
	gaiaToolsError(p_dst        == NULL, "invalid destination memory",   return 0);
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",        return 0);
	gaiaToolsError(p_src        == NULL, "invalid source buffer memory", return 0);

	memcpy(p_dst, (void*)(&((char*)p_src)[src_offset]), size);
	(*p_dst_offset) += size;

	return 1;
}

uint8_t gaiaReadReal(
    gaia_real* p_val,
    uint32_t   src_offset,
    uint32_t*  p_dst_offset,
    void*      p_src
) {
	gaiaToolsError(p_val        == NULL, "invalid destination value memory", return 0);
	gaiaToolsError(p_dst_offset == NULL, "invalid offset memory",            return 0);
	gaiaToolsError(p_src        == NULL, "invalid source buffer memory",     return 0);

#ifndef GAIA_DOUBLE_PRECISION
	double _val;
	memcpy(&_val, (void*)(&((char*)p_src)[src_offset]), 8);
	(*p_val) = (gaia_real)_val;
	(*p_dst_offset) += sizeof(gaia_real);
#else
	gaiaReadBuffer((void*)p_val, sizeof(gaia_real), src_offset, p_dst_offset, p_src);
#endif//GAIA_DOUBLE_PRECISION

	return 1;
}

void* gaiaProcessSourceExtendedId(
    char*                  p_bodies,
    uint32_t               body_idx, 
    GaiaCelestialBodyFlags flags, 
    char*                  p_source_extended_id
) {
	gaiaToolsError(p_bodies == NULL, "invalid source bodies", return NULL);

	GaiaCelestialBodyFlags _flags = flags;
	(_flags & GAIA_SOURCE_EXTENDED_ID) && (_flags &= ~GAIA_SOURCE_EXTENDED_ID);

	uint32_t body_size = gaiaGetBodySize(_flags);
	uint32_t source_extended_ids_size = 0;

	for (uint32_t _body_idx = 0; _body_idx < body_idx; _body_idx++) {
		uint8_t id_length = (uint8_t)p_bodies[body_size * _body_idx + source_extended_ids_size];
		source_extended_ids_size += id_length + 1;//null character
	}

	char* p_body = &((char*)p_bodies)[body_size * body_idx + source_extended_ids_size];

	uint8_t id_length = (uint8_t)p_body[0];
	char* id_start = &p_body[1];
	
	memcpy(p_source_extended_id, id_start, id_length);
	p_source_extended_id[id_length] = '\0';

	return &p_body[id_length + 1];//address at first value after source extended id
}

uint8_t gaiaReadBinaryFile(
	const char*            src_path, 
	GaiaCelestialBodyFlags flags,
	uint32_t               offset, 
	uint32_t               size, 
	uint32_t*              p_dst_size, 
	void**                 pp_dst
) {
	gaiaToolsError(pp_dst     == NULL, "invalid destination buffer memory", return 0);
	gaiaToolsError(p_dst_size == NULL, "invalid destination size memory", return 0);

	FILE* src_stream = fopen(src_path, "rb");
	gaiaToolsError(src_path == NULL || src_stream == NULL, "invalid file data", return 0);

	fseek(src_stream, 0, SEEK_END);
	uint32_t src_size = ftell(src_stream);
	fseek(src_stream, 0, SEEK_SET);

	void* p_src = calloc(1, src_size * 2);
	gaiaToolsError(p_src == NULL, "invalid source file memory", return 0);

	fread(p_src, 1, src_size, src_stream);

	uint32_t _dst_size = size;
	if (_dst_size == 0) {
		_dst_size = (src_size - offset) / GAIA_CELESTIAL_BODY_MAX_SIZE * gaiaGetBodySize(flags);
	}
	(*pp_dst) = calloc(1, _dst_size);
	gaiaToolsError(pp_dst == NULL, "invalid destination", return 0);

	gaiaExtractBuffer(p_src, src_size, offset, flags, _dst_size, *pp_dst);

	(*p_dst_size) = _dst_size;

	fclose(src_stream);
	free(p_src);

	return 1;
}

uint8_t gaiaReadBinaryFileFromID(
    const char*            src_dir, 
    uint32_t               src_id, 
    GaiaCelestialBodyFlags flags, 
    uint32_t               offset, 
    uint32_t               size, 
    uint32_t*              p_dst_size, 
    void**                 pp_dst
) {
	gaiaToolsError(src_dir    == NULL, "invalid src dir memory",     return 0);
	gaiaToolsError(p_dst_size == NULL, "invalid dst size memory",    return 0);
	gaiaToolsError(pp_dst     == NULL, "invalid destination memory", return 0);

	char s_src_id[5] = "0000";
	gaiaUniverseModelGetId(src_id, s_src_id);
	char src_path[512];
	strcpy(src_path, src_dir);
	strcat(src_path, "/gaiaUniverseModel_");
	strcat(src_path, s_src_id);
	strcat(src_path, ".bin");

	gaiaReadBinaryFile(src_path, flags, offset, size, p_dst_size, pp_dst);
	
	return 1;
}

uint8_t gaiaExtractBuffer(
    void*                  p_src,
    uint32_t               src_buffer_size,
    uint32_t               offset,
    GaiaCelestialBodyFlags flags, 
    uint32_t               dst_size, 
    void*                  p_dst
) {
	gaiaToolsError(p_src == NULL, "invalid src memory", return 0);
	gaiaToolsError(p_dst == NULL, "invalid dst memory", return 0);

	uint32_t src_offset = offset;
	uint32_t dst_offset = 0;

	uint8_t source_extended_id_size = 0;

	while (src_offset < src_buffer_size) {
		if (flags & GAIA_SOURCE_EXTENDED_ID) {
			gaiaReadBuffer((void*)(&((char*)p_dst)[dst_offset]), GAIA_SOURCE_EXTENDED_ID_SIZE - 1, src_offset, &dst_offset, p_src);
			((char*)p_dst)[dst_offset] = '\0';
			dst_offset++;
		}
		src_offset += GAIA_SOURCE_EXTENDED_ID_SIZE;

		if (flags & GAIA_SOURCE_ID) { 
			gaiaReadLong((uint64_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 8;

		if (flags & GAIA_SOLUTION_ID) { 
			gaiaReadLong((uint64_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 8;

		if (flags & GAIA_RA) { 
			gaiaReadReal((gaia_real*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 8;
		if (flags & GAIA_DEC) { 
			gaiaReadReal((gaia_real*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 8;

		if (flags & GAIA_BARYCENTRIC_DISTANCE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_PMRA) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_PMDEC) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_RADIAL_VELOCITY) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MAG_G) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MAG_BP) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MAG_RP) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MAG_RVS) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_V_I) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MEAN_ABSOLUTE_V) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_AG) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_AV) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_TEFF) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_LOGG) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_FEH) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_ALPHAFE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MBOL) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_AGE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_MASS) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_RADIUS) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_VSINI) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_POPULATION) { 
			gaiaReadByte((uint8_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 1;

		if (flags & GAIA_HAS_PHOTOCENTER_MOTION) { 
			gaiaReadByte((uint8_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 1;

		if (flags & GAIA_NC) { 
			gaiaReadInt((uint32_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_NT) { 
			gaiaReadInt((uint32_t*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_SEMIMAJOR_AXIS) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_ECCENTRICITY) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_INCLINATION) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;

		if (flags & GAIA_LONGITUDE_ASCENDING_NODE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_ORBIT_PERIOD) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_PERIASTRON_DATE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_PERIASTRON_ARGUMENT) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_VARIABILITY_AMPLITUDE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_VARIABILITY_PERIOD) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (flags & GAIA_VARIABILITY_PHASE) { 
			gaiaReadFloat((float*)(&((char*)p_dst)[dst_offset]), src_offset, &dst_offset, p_src); 
		}
		src_offset += 4;
		
		if (dst_offset >= dst_size) { break; }
	}

	return 1;
}

uint8_t gaiaConvertCSV(
    const char* src_path, 
    const char* dst_path, 
    uint32_t    body_count
) {
	gaiaToolsError(src_path == NULL, "invalid src path memory", return 0);
	gaiaToolsError(dst_path == NULL, "invalid dst path memory", return 0);

	CsvHandle csv = CsvOpen(src_path);
	char* row = CsvReadNextRow(csv);

	uint32_t src_body_count = 0;
	if (body_count != UINT32_MAX) {
		src_body_count = body_count;
	}
	else {
		while (CsvReadNextRow(csv) != NULL) {
			src_body_count++;
		}
	}
	CsvClose(csv);

	uint32_t dst_offset = 0;
	void* p_dst = calloc(src_body_count, GAIA_CELESTIAL_BODY_MAX_SIZE);
	gaiaToolsError(p_dst == NULL, "invalid destination buffer memory", return 0);


	csv = CsvOpen(src_path);
	row = CsvReadNextRow(csv);
	for (uint32_t i = 0; row != NULL && i < body_count; i++) {
		row = CsvReadNextRow(csv);
		if (row != NULL) {
			for (uint32_t j = 0; j < GAIA_BODY_VARIABLES; j++) {
				char* column = (char*)CsvReadNextCol(row, csv);
				char* end_column = &column[strlen(column) - 1];
				if (column != NULL) {
					switch (j) {
					case SOURCE_EXTENDED_ID_IDX: 
						gaiaWriteBuffer((void*)column, GAIA_SOURCE_EXTENDED_ID_SIZE, &dst_offset, p_dst); break;
					case SOURCE_ID_IDX:
						gaiaWriteLong((uint64_t)strtol(column, &end_column, 10), &dst_offset, p_dst); break;
					case SOLUTION_ID_IDX:
						gaiaWriteLong((uint64_t)strtol(column, &end_column, 10), &dst_offset, p_dst); break;
					case RA_IDX:
						gaiaWriteDouble((double)strtof(column, &end_column), &dst_offset, p_dst); break;
					case DEC_IDX:
						gaiaWriteDouble((double)strtof(column, &end_column), &dst_offset, p_dst); break;
					case BARYCENTRIC_DISTANCE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case PMRA_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case PMDEC_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case RADIAL_VELOCITY_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MAG_G_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MAG_BP_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MAG_RP_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MAG_RVS_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case V_I_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MEAN_ABSOLUTE_V_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case AG_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case AV_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case TEFF_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case LOGG_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case FEH_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case ALPHAFE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MBOL_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case AGE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case MASS_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case RADIUS_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case VSINI_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case POPULATION_IDX:
						gaiaWriteByte((uint8_t)strtol(column, &end_column, 10), &dst_offset, p_dst); break;
					case HAS_PHOTOCENTER_MOTION_IDX:
						gaiaWriteBoolean(column, &dst_offset, p_dst); break;
					case NC_IDX:
						gaiaWriteInt((uint32_t)strtol(column, &end_column, 10), &dst_offset, p_dst); break;
					case NT_IDX:
						gaiaWriteInt((uint32_t)strtol(column, &end_column, 10), &dst_offset, p_dst); break;
					case SEMIMAJOR_AXIS_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case ECCENTRICITY_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case INCLINATION_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case LONGITUDE_ASCENDING_NODE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case ORBIT_PERIOD_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case PERIASTRON_DATE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case PERIASTRON_ARGUMENT_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case VARIABILITY_AMPLITUDE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case VARIABILITY_PERIOD_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					case VARIABILITY_PHASE_IDX:
						gaiaWriteFloat((float)strtof(column, &end_column), &dst_offset, p_dst); break;
					}
				}
			}
		}
	}

	FILE* dst_stream = fopen(dst_path, "wb");
	gaiaToolsError(dst_stream == NULL, "invalid destination path", return 0);

	fwrite(p_dst, src_body_count, GAIA_CELESTIAL_BODY_MAX_SIZE, dst_stream);

	free(p_dst);
	fclose(dst_stream);
	CsvClose(csv);

	return 1;
}

uint8_t gaiaSplit(
	const char* src_dir,
	uint32_t    src_id
) {
	gaiaToolsError(src_dir == NULL, "invalid source directory", return 0);

	char dst_0_path[256]; char dst_1_path[256];
	
	char src_path[256];
	strcpy(src_path, src_dir);
	strcat(src_path, "/gaiaUniverseModel_");

	char s_src_id[5] = "0000";
	gaiaUniverseModelGetId(src_id, s_src_id);;
	strcat(src_path, s_src_id);

	strcpy(dst_0_path, src_path);
	strcpy(dst_1_path, src_path);

	strcat(src_path, ".bin");

	strcat(dst_0_path, ".0.bin");
	strcat(dst_1_path, ".1.bin");

	FILE* src_stream = fopen(src_path, "rb");
	
	fseek(src_stream, 0, SEEK_END);
	uint32_t dst_size_0 = 0;
	uint32_t dst_size_1 = 0;
	{
		uint32_t dst_size = ((uint32_t)ftell(src_stream) / (uint32_t)GAIA_CELESTIAL_BODY_MAX_SIZE);
		if (dst_size % 2 == 1) {
			dst_size_0 = (dst_size - 1) / 2 * (uint32_t)GAIA_CELESTIAL_BODY_MAX_SIZE;
			dst_size_1 = (dst_size + 1) / 2 * (uint32_t)GAIA_CELESTIAL_BODY_MAX_SIZE;
		}
		else if (dst_size % 2 == 0) {
			dst_size_0 = dst_size / 2 * (uint32_t)GAIA_CELESTIAL_BODY_MAX_SIZE;
			dst_size_1 = dst_size / 2 * (uint32_t)GAIA_CELESTIAL_BODY_MAX_SIZE;
		}
	}
	
	fseek(src_stream, 0, SEEK_SET);

	FILE* dst_0_stream = fopen(dst_0_path, "wb");
	FILE* dst_1_stream = fopen(dst_1_path, "wb");
	void* dst_0_buffer = calloc(1, dst_size_0);
	void* dst_1_buffer = calloc(1, dst_size_1);
	gaiaToolsError(dst_0_buffer == NULL || dst_1_buffer == NULL, "invalid destination buffers", return 0);

	fread(dst_0_buffer, 1, dst_size_0, src_stream);
	fseek(src_stream, dst_size_0, SEEK_SET);
	fread(dst_1_buffer, 1, dst_size_1, src_stream);

	fwrite(dst_0_buffer, 1, dst_size_0, dst_0_stream);
	fwrite(dst_1_buffer, 1, dst_size_1, dst_1_stream);
	
	free(dst_0_buffer);
	free(dst_1_buffer);
	fclose(src_stream);
	fclose(dst_0_stream);
	fclose(dst_1_stream);

	return 1;
}



#ifdef  __cplusplus
}
#endif//__cplusplus