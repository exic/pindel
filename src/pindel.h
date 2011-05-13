/* 
 * File:   pindel.h
 * Author: david
 *
 * Created on 13 mei 2011, 10:15
 */

#ifndef PINDEL_H
#define	PINDEL_H

#include <string>
#include <vector>
#include "khash.h"
#include "sam.h"

/*
 * Global variables defined in pindel.c
 */
extern int ADDITIONAL_MISMATCH;
extern double Seq_Error_Rate;
extern char Match2N[256];
extern int Min_Perfect_Match_Around_BP;
extern double MaximumAllowedMismatchRate;
extern short ReportLength;
extern
	std::vector <
	std::string >
	VectorTag;
extern
	std::string
	CurrentChrMask;
extern unsigned int
	NumberOfSIsInstances;
extern unsigned int
	NumberOfDIInstances;
extern unsigned int
	NumberOfTDInstances;
extern unsigned int
	NumberOfDeletionsInstances;
extern unsigned int
	NumberOfInvInstances;
extern unsigned int
	NumRead2ReportCutOff;
extern unsigned int
	BalanceCutoff;
extern int
	NumRead2ReportCutOff_BP;
extern char
	Cap2LowArray[256];
extern int
	g_maxPos;
extern unsigned int
	CONS_Chr_Size;
extern bool
	FirstChr;
extern unsigned int
	NumReadScanned;
extern unsigned int
	NumReadInChr;
extern unsigned int
	InChrPlus;
extern unsigned int
	InChrMinus;
extern unsigned int
	GetPlus;
extern unsigned int
	GetMinus;
extern int
	g_binIndex;
extern int
	WINDOW_SIZE;
/*
 * Constants
 */
const char
	SENSE = '+';
const char
	ANTISENSE = '-';
const char
	FORWARD = '+';
const char
	BACKWARD = '-';
const
	std::string
	N_str = "N";
const char
	N_char = 'N';
const char
	BD_char = 'A';
const short
	Max_uint8_t = 100;
const unsigned
	SpacerBeforeAfter = 10000000;
const char
	Plus = '+';
const char
	Minus = '-';
const char
	FirstCharReadName = '@';
const short
	Max_short = 128;
const int
	NumberOfReadsPerBuffer = 1000;	// estimate later


/*
 * Data structures
 */
struct UniquePoint
{
	short
		LengthStr;
	unsigned int
		AbsLoc;
	char
		Direction;									// forward reverse
	char
		Strand;											// sense antisense
	short
		Mismatches;
};

struct SPLIT_READ
{
	SPLIT_READ ()
	{
		FragName = "";
		Name = "";
		UnmatchedSeq = "";
		HalfMapped = "";
		HalfUnmapped = "";
		MatchedD = 0;
		MatchedRelPos = 0;
		MS = 0;
		InsertSize = 0;
		Tag = "";
		ReadLength = 0;
		ReadLengthMinus = 0;
		MAX_SNP_ERROR = 0;
		TOTAL_SNP_ERROR_CHECKED = 0;
		TOTAL_SNP_ERROR_CHECKED_Minus = 0;
		MinClose = 0;
		BP = 0;
		Left = 0;
		Right = 0;
		BPLeft = 0;
		BPRight = 0;
		IndelSize = 0;
		Unique = false;
		score = 0.0;
		InsertedStr = "";
		NT_str = "";
		NT_size = 0;
		Used = false;
		CloseEndLength = 0;
		Found = false;
		LeftMostPos = 0;
	}
	std::string
		FragName;
	std::string Name;
	std::string UnmatchedSeq;
	std::string HalfMapped;
	std::string HalfUnmapped;
	char
		MatchedD;
	unsigned int
		MatchedRelPos;
	short
		MS;
	short
		InsertSize;
	std::string Tag;
	std::vector < UniquePoint > UP_Close;	// partial alignment of the unmapped reads close to the mapped read
	std::vector < UniquePoint > UP_Far;
	std::vector < UniquePoint > UP_Far_backup;
	short
		ReadLength;
	short
		ReadLengthMinus;
	short
		MAX_SNP_ERROR;							// = (short)(Temp_One_Read.UnmatchedSeq.size() * Seq_Error_Rate);

	short
		TOTAL_SNP_ERROR_CHECKED;		// = MAX_SNP_ERROR + ADDITIONAL_MISMATCH + 1;
	short
		TOTAL_SNP_ERROR_CHECKED_Minus;	// = MAX_SNP_ERROR + ADDITIONAL_MISMATCH;
	short
		MinClose;
	short
		BP;
	int
		Left;
	int
		Right;
	unsigned int
		BPLeft;
	unsigned int
		BPRight;
	unsigned int
		IndelSize;
	bool
		Unique;
	double
		score;
	std::string InsertedStr;
	std::string NT_str;
	short
		NT_size;
	//string NT_2str;
	//short NT_2size;
	bool
		Used;
	short
		CloseEndLength;
	bool
		Found;
	int
		LeftMostPos;
};

struct SupportPerSample
{
	int
		NumPlus;
	int
		NumMinus;
	int
		NumUPlus;
	int
		NumUMinus;
};

struct Indel4output
{
	Indel4output ()
	{
		BPLeft = 0;
		BPRight = 0;
		IndelSize = 0;
		Start = 0;
		End = 0;
		RealStart = 0;
		RealEnd = 0;
		NT_size = 0;
		WhetherReport = false;
		IndelStr = "";
		Support = 0;
	}
	unsigned int
		BPLeft;
	unsigned int
		BPRight;
	unsigned int
		IndelSize;
	unsigned int
		Start;
	unsigned int
		End;
	unsigned int
		RealStart;
	unsigned int
		RealEnd;
	short
		NT_size;
	bool
		WhetherReport;
	std::string IndelStr;
	unsigned short
		Support;
};

struct LI_Pos
{
	LI_Pos ()
	{
		Plus_Pos = 0;
		Minus_Pos = 0;
		WhetherReport = false;
	}
	unsigned
		Plus_Pos;
	unsigned
		Minus_Pos;
	std::vector < unsigned >
		Plus_Reads;									// put index here
	std::vector < unsigned >
		Minus_Reads;
	bool
		WhetherReport;
};

struct Rest_Pos
{
	Rest_Pos ()
	{
		Strand = 'X';
		Pos = 0;
	}
	char
		Strand;
	unsigned
		Pos;
	std::vector < unsigned >
		Pos_Reads;									// put index here
};

struct flagshit
{
	flagshit ()
	{
		mapped = false;
		unique = false;
		sw = false;
		edits = 0;
		suboptimal = false;
	}
	bool
		mapped;
	bool
		unique;
	bool
		sw;
	int
		edits;
	bool
		suboptimal;
};

/*
 * Function definitions
 */
void
ReadInOneChr (std::ifstream & inf_Seq, std::string & TheInput,
							const std::string & ChrName);
void
parse_flags_and_tags (const bam1_t * b, flagshit * flags);
int32_t
bam_cigar2len (const bam1_core_t * c, const uint32_t * cigar);
static int
fetch_func (const bam1_t * b1, void *data);
void
build_record (const bam1_t * mapped_read, const bam1_t * unmapped_read,
							void *data);

#ifdef __cplusplus
extern
	"C"
{
	int32_t
	bam_get_tid (const bam_header_t * header, const char *seq_name);
	int32_t
	bam_aux2i (const uint8_t * s);
	void
	bam_init_header_hash (bam_header_t * header);
}
#endif

std::vector <
	std::string >
ReverseComplement (const std::vector < std::string > &input);
std::string ReverseComplement (const std::string & InputPattern);
std::string Cap2Low (const std::string & input);
void GetRealStart4Insertion (const std::string & TheInput,
														 const std::string & InsertedStr,
														 unsigned int &RealStart, unsigned int &RealEnd);
void GetRealStart4Deletion (const std::string & TheInput,
														unsigned int &RealStart, unsigned int &RealEnd);
bool ReportEvent (const std::vector < SPLIT_READ > &Deletions,
									const unsigned int &Pre_S, const unsigned int &Pre_E);
void GetCloseEnd (const std::string & CurrentChr, SPLIT_READ & Temp_One_Read);
void GetFarEnd_BothStrands (const std::string & CurrentChr,
														SPLIT_READ & Temp_One_Read,
														const short &RangeIndex);
void GetFarEnd_OtherStrand (const std::string & CurrentChr,
														SPLIT_READ & Temp_One_Read,
														const short &RangeIndex);
void GetFarEnd_SingleStrandDownStream (const std::string & CurrentChr,
																			 SPLIT_READ & Temp_One_Read,
																			 const short &RangeIndex);
void GetFarEnd_SingleStrandUpStream (const std::string & CurrentChr,
																		 SPLIT_READ & Temp_One_Read,
																		 const short &RangeIndex);
void GetFarEnd_SingleStrandDownStreamInsertions (const std::
																								 string & CurrentChr,
																								 SPLIT_READ & Temp_One_Read,
																								 const short &RangeIndex);
void GetFarEnd (const std::string & CurrentChr, SPLIT_READ & Temp_One_Read,
								const int &start, const int &end);
void OutputDeletions (const std::vector < SPLIT_READ > &Deletions,
											const std::string & TheInput, const unsigned int &C_S,
											const unsigned int &C_E, const unsigned int &RealStart,
											const unsigned int &RealEnd,
											std::ofstream & DeletionOutf);

void OutputTDs (const std::vector < SPLIT_READ > &TDs,
								const std::string & TheInput,
								const unsigned int &C_S,
								const unsigned int &C_E,
								const unsigned int &RealStart,
								const unsigned int &RealEnd, std::ofstream & TDOutf);


void OutputInversions (const std::vector < SPLIT_READ > &Inv,
											 const std::string & TheInput,
											 const unsigned int &C_S,
											 const unsigned int &C_E,
											 const unsigned int &RealStart,
											 const unsigned int &RealEnd, std::ofstream & InvOutf);

void OutputSIs (const std::vector < SPLIT_READ > &SIs,
								const std::string & TheInput,
								const unsigned int &C_S,
								const unsigned int &C_E,
								const unsigned int &RealStart,
								const unsigned int &RealEnd, std::ofstream & SIsOutf);

short CompareTwoReads (const SPLIT_READ & First, const SPLIT_READ & Second);
std::string Reverse (const std::string & InputPattern);
std::string Cap2Low (const std::string & input);


void CheckBoth (const SPLIT_READ & OneRead,
								const std::string & TheInput,
								const std::string & CurrentReadSeq,
								const std::vector < unsigned int >PD_Plus[],
								const std::vector < unsigned int >PD_Minus[],
								const short &BP_Start,
								const short &BP_End,
								const short &CurrentLength, std::vector < UniquePoint > &UP);

//void ProcessLIs(vector <SPLIT_READ> & LIs, ofstream & LIoutputfile);
bool NotInVector (const std::string & OneTag,
									const std::vector < std::string > &VectorTag);
void GetIndelTypeAndRealStart (const std::string & TheInput,
															 const unsigned int &BPLeft,
															 const unsigned int &IndelSize,
															 const std::string & IndelStr,
															 std::string & IndelType,
															 unsigned int &RealStart,
															 const bool & WhetherD);
void CleanUniquePoints (std::vector < UniquePoint > &Input_UP);
#endif /* PINDEL_H */