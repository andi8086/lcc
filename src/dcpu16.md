%{
enum {RGA=0, RGB=1, RGC=2, RGX=3, RGY=4, RGZ=5, RGI=6};

#include "c.h"

#define TMP_REG 0x07
#define VAR_REG (0x7F ^ TMP_REG)

#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)
#ifdef NDEBUG 
#undef NDEBUG 
#endif 


// Declare local routines to be used by IR record here 
static void address(Symbol, Symbol, long); 
static void blkfetch(int, int, int, int); 
static void blkloop(int, int, int, int, int, int[]); 
static void blkstore(int, int, int, int); 
static void defaddress(Symbol); 
static void defconst(int, int, Value); 
static void defstring(int, char *); 
static void defsymbol(Symbol); 
static void doarg(Node); 
static void emit2(Node); 
static void export(Symbol); 
static void clobber(Node); 
static void function(Symbol, Symbol [], Symbol [], int);
static void global(Symbol); 
static void import(Symbol); 
static void local(Symbol); 
static void progbeg(int, char **); 
static void progend(void); 
static void segment(int); 
static void space(int); 
static void target(Node);
static int memop(Node);
static int sametree(Node,Node);
static int isfptr(Node,int,int);

static void pushstack(int n);
static void popstack(int n);

// Local vars here

static Symbol reg[32];
static Symbol regw;

%}

%start stmt
%term CNSTF1=1041
%term CNSTI1=1045
%term CNSTP1=1047
%term CNSTU1=1046
%term ARGB=41
%term ARGF1=1057
%term ARGI1=1061
%term ARGP1=1063
%term ARGU1=1062
%term ASGNB=57
%term ASGNF1=1073
%term ASGNI1=1077
%term ASGNP1=1079
%term ASGNU1=1078
%term INDIRB=73
%term INDIRF1=1089
%term INDIRI1=1093
%term INDIRP1=1095
%term INDIRU1=1094
%term CVFF1=1137
%term CVFI1=1141
%term CVIF1=1153
%term CVII1=1157
%term CVIU1=1158
%term CVPU1=1174
%term CVUI1=1205
%term CVUP1=1207
%term CVUU1=1206
%term NEGF1=1217
%term NEGI1=1221
%term CALLB=217
%term CALLF1=1233
%term CALLI1=1237
%term CALLP1=1239
%term CALLU1=1238
%term CALLV=216
%term RETF1=1265
%term RETI1=1269
%term RETP1=1271
%term RETU1=1270
%term RETV=248
%term ADDRGP1=1287
%term ADDRFP1=1303
%term ADDRLP1=1319
%term ADDF1=1329
%term ADDI1=1333
%term ADDP1=1335
%term ADDU1=1334
%term SUBF1=1345
%term SUBI1=1349
%term SUBP1=1351
%term SUBU1=1350
%term LSHI1=1365
%term LSHU1=1366
%term MODI1=1381
%term MODU1=1382
%term RSHI1=1397
%term RSHU1=1398
%term BANDI1=1413
%term BANDU1=1414
%term BCOMI1=1429
%term BCOMU1=1430
%term BORI1=1445
%term BORU1=1446
%term BXORI1=1461
%term BXORU1=1462
%term DIVF1=1473
%term DIVI1=1477
%term DIVU1=1478
%term MULF1=1489
%term MULI1=1493
%term MULU1=1494
%term EQF1=1505
%term EQI1=1509
%term EQU1=1510
%term GEF1=1521
%term GEI1=1525
%term GEU1=1526
%term GTF1=1537
%term GTI1=1541
%term GTU1=1542
%term LEF1=1553
%term LEI1=1557
%term LEU1=1558
%term LTF1=1569
%term LTI1=1573
%term LTU1=1574
%term NEF1=1585
%term NEI1=1589
%term NEU1=1590
%term JUMPV=584
%term LABELV=600
%term VREGP=711

%term LOADB=233
%term LOADF1=1249
%term LOADP1=1255
%term LOADI1=1253
%term LOADU1=1254

%%

reg:    LOADF1(reg) "?SET %c, %0\n" move(a)
reg:    LOADI1(reg) "?SET %c, %0\n" move(a)
reg:    LOADU1(reg) "?SET %c, %0\n" move(a)
reg:    LOADP1(reg) "?SET %c, %0\n" move(a)

reg:    INDIRF1(VREGP)  "# read register\n"
reg:    INDIRI1(VREGP)  "# read register\n"
reg:    INDIRU1(VREGP)  "# read register\n"
reg:    INDIRP1(VREGP)  "# read register\n"

stmt:   ASGNF1(VREGP,reg)   "# write register\n"
stmt:   ASGNI1(VREGP,reg)   "# write register\n"
stmt:   ASGNU1(VREGP,reg)   "# write register\n"
stmt:   ASGNP1(VREGP,reg)   "# write register\n"

stmt:   reg ""

con:    CNSTI1  "%a" 1
con:    CNSTU1  "%a" 1
con:    CNSTP1  "%a" 1

acon:   CNSTU1  "%a" 1
acon:   CNSTP1  "%a" 1

addr:   acon            "%0"
addr:   ADDI1(reg,acon) "%1+%0"
addr:   reg             "%0"
addr:   ADDRGP1         "%a"
addr:   ADDRFP1         "#" 1
addr:   ADDRLP1         "#" 1

reg:    con "SET %c, %0\n" 1

mem:    INDIRF1(addr)   "[%0]"
mem:    INDIRI1(addr)   "[%0]"
mem:    INDIRU1(addr)   "[%0]"
mem:    INDIRP1(addr)   "[%0]"

aval:   addr    "[%0]"
aval:   reg     "%0"
bval:   reg     "%0"
bval:   con     "%0"
bval:   mem     "%0"

stmt:   ASGNF1(aval,bval)   "?SET %0, %1\n" 1
stmt:   ASGNI1(aval,bval)   "?SET %0, %1\n" 1
stmt:   ASGNU1(aval,bval)   "?SET %0, %1\n" 1
stmt:   ASGNP1(aval,bval)   "?SET %0, %1\n" 1

reg:    BCOMI1(bval)                "SET %c, 0xffff\nXOR %c, %0\n" 3
reg:    BCOMU1(bval)                "SET %c, 0xffff\nXOR %c, %0\n" 3
stmt:   ASGNI1(mem,BCOMI1(bval))    "SET %c, 0xffff\nXOR %c, %0\n" 3
stmt:   ASGNU1(mem,BCOMU1(bval))    "SET %c, 0xffff\nXOR %c, %0\n" 3

reg:    CVFI1(bval)             "SET %c, %0\n" 1
stmt:   ASGNI1(mem,CVFI1(bval)) "SET %c, %0\n" 1

reg:    CVIF1(bval)                "SET %c, %0\n" 1
stmt:   ASGNF1(mem,CVIF1(bval))    "SET %c, %0\n" 1 
reg:    CVIU1(bval)                "SET %c, %0\n" 1
stmt:   ASGNU1(mem,CVIF1(bval))    "SET %c, %0\n" 1

reg:    CVUI1(bval)                "SET %c, %0\n" 1
stmt:   ASGNI1(mem,CVUI1(bval))    "SET %c, %0\n" 1
reg:    CVUP1(bval)                "SET %c, %0\n" 1
stmt:   ASGNP1(mem,CVUP1(bval))    "SET %c, %0\n" 1

reg:    CVPU1(bval)                "SET %c, %0\n" 1
stmt:   ASGNU1(mem,CVPU1(bval))    "SET %c, %0\n" 1

reg:    NEGF1(bval)                "SET %c, 0x0000\nSUB %c, %0\n" 4
stmt:   ASGNF1(mem,NEGI1(bval))    "SET %c, 0x0000\nSUB %c, %0\n" 4
reg:    NEGI1(bval)                "SET %c, 0x0000\nSUB %c, %0\n" 4
stmt:   ASGNI1(mem,NEGI1(bval))    "SET %c, 0x0000\nSUB %c, %0\n" 4

reg:    ADDF1(bval,bval)                "SET %c, %0\nADD %c, %1\n" 3 
stmt:   ASGNF1(mem,ADDF1(bval,bval))    "SET %c, %0\nADD %c, %1\n" 3 
reg:    ADDI1(bval,bval)                "SET %c, %0\nADD %c, %1\n" 3
stmt:   ASGNI1(mem,ADDI1(bval,bval))    "SET %c, %0\nADD %c, %1\n" 3
reg:    ADDU1(bval,bval)                "SET %c, %0\nADD %c, %1\n" 3
stmt:   ASGNU1(mem,ADDU1(bval,bval))    "SET %c, %0\nADD %c, %1\n" 3
reg:    ADDP1(bval,bval)                "SET %c, %0\nADD %c, %1\n" 3
stmt:   ASGNP1(mem,ADDP1(bval,bval))    "SET %c, %0\nADD %c, %1\n" 3

reg:    BANDI1(bval,bval)                "SET %c, %0\nAND %c, %1\n" 2
stmt:   ASGNI1(mem,BANDI1(bval,bval))    "SET %c, %0\nAND %c, %1\n" 2
reg:    BANDU1(bval,bval)                "SET %c, %0\nAND %c, %1\n" 2
stmt:   ASGNU1(mem,BANDU1(bval,bval))    "SET %c, %0\nAND %c, %1\n" 2

reg:    BORI1(bval,bval)                "SET %c, %0\nBOR %c, %1\n" 2
stmt:   ASGNI1(mem,BORI1(bval,bval))    "SET %c, %0\nBOR %c, %1\n" 2
reg:    BORU1(bval,bval)                "SET %c, %0\nBOR %c, %1\n" 2
stmt:   ASGNU1(mem,BORU1(bval,bval))    "SET %c, %0\nBOR %c, %1\n" 2

reg:    BXORI1(bval,bval)                "SET %c, %0\nXOR %c, %1\n" 2
stmt:   ASGNI1(mem,BXORI1(bval,bval))    "SET %c, %0\nXOR %c, %1\n" 2
reg:    BXORU1(bval,bval)                "SET %c, %0\nXOR %c, %1\n" 2
stmt:   ASGNU1(mem,BXORU1(bval,bval))    "SET %c, %0\nXOR %c, %1\n" 2

reg:    DIVF1(bval,bval)                "SET %c, %0\nDIV %c, %1\n" 4 
stmt:   ASGNF1(mem,DIVF1(bval,bval))    "SET %c, %0\nDIV %c, %1\n" 4 
reg:    DIVI1(bval,bval)                "SET %c, %0\nDIV %c, %1\n" 4
stmt:   ASGNI1(mem,DIVI1(bval,bval))    "SET %c, %0\nDIV %c, %1\n" 4
reg:    DIVU1(bval,bval)                "SET %c, %0\nDIV %c, %1\n" 4
stmt:   ASGNU1(mem,DIVU1(bval,bval))    "SET %c, %0\nDIV %c, %1\n" 4

reg:    LSHI1(bval,bval)                "SET %c, %0\nSHL: %c, %0\n" 3
stmt:   ASGNI1(mem,LSHI1(bval,bval))    "SET %c, %0\nSHL: %c, %0\n" 3
reg:    LSHU1(bval,bval)                "SET %c, %0\nSHL: %c, %0\n" 3
stmt:   ASGNU1(mem,LSHU1(bval,bval))    "SET %c, %0\nSHL: %c, %0\n" 3

reg:    MODI1(bval,bval)                "SET %c, %0\nMOD %c, %1\n" 4
stmt:   ASGNI1(mem,MODI1(bval,bval))    "SET %c, %0\nMOD %c, %1\n" 4
reg:    MODU1(bval,bval)                "SET %c, %0\nMOD %c, %1\n" 4
stmt:   ASGNU1(mem,MODU1(bval,bval))    "SET %c, %0\nMOD %c, %1\n" 4

reg:    MULF1(bval,bval)                "SET %c, %0\nMUL %c, %1\n" 3 
stmt:   ASGNI1(mem,MULF1(bval,bval))    "SET %c, %0\nMUL %c, %1\n" 3 
reg:    MULI1(bval,bval)                "SET %c, %0\nMUL %c, %1\n" 3
stmt:   ASGNI1(mem,MULI1(bval,bval))    "SET %c, %0\nMUL %c, %1\n" 3
reg:    MULU1(bval,bval)                "SET %c, %0\nMUL %c, %1\n" 3
stmt:   ASGNU1(mem,MULU1(bval,bval))    "SET %c, %0\nMUL %c, %1\n" 3

reg:    RSHI1(bval,bval)                "SET %c, %0\nSHR: %c, %0\n" 3
stmt:   ASGNI1(mem,RSHI1(bval,bval))    "SET %c, %0\nSHR: %c, %0\n" 3
reg:    RSHU1(bval,bval)                "SET %c, %0\nSHR: %c, %0\n" 3
stmt:   ASGNU1(mem,RSHU1(bval,bval))    "SET %c, %0\nSHR: %c, %0\n" 3

reg:    SUBF1(bval,bval)                "SET %c, %0\nSUB %c, %1\n" 3 
stmt:   ASGNF1(mem,SUBF1(bval,bval))    "SET %c, %0\nSUB %c, %1\n" 3 
reg:    SUBI1(bval,bval)                "SET %c, %0\nSUB %c, %1\n" 3
stmt:   ASGNI1(mem,SUBI1(bval,bval))    "SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBU1(bval,bval)                "SET %c, %0\nSUB %c, %1\n" 3
stmt:   ASGNU1(mem,SUBU1(bval,bval))    "SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBP1(bval,bval)                "SET %c, %0\nSUB %c, %1\n" 3
stmt:   ASGNP1(mem,SUBP1(bval,bval))    "SET %c, %0\nSUB %c, %1\n" 3

stmt:   EQF1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4 
stmt:   EQI1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4
stmt:   EQU1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4

stmt:   GEF1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6 
stmt:   GEI1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6
stmt:   GEU1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6

stmt:   GTF1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4 
stmt:   GTI1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4
stmt:   GTU1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4

stmt:   LEF1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0 %1\nSET PC %a\n" 6 
stmt:   LEI1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0 %1\nSET PC %a\n" 6
stmt:   LEU1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0 %1\nSET PC %a\n" 6

stmt:   LTF1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4 
stmt:   LTI1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4
stmt:   LTU1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4

stmt:   NEF1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4 
stmt:   NEI1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4
stmt:   NEU1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4

stmt:   ARGF1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGI1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGU1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGP1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ASGNB(addr,INDIRB(addr))    "# block assign\n" 1

reg:    CALLF1(addr)    "^JSR %0\n" 2
reg:    CALLI1(addr)    "^JSR %0\n" 2
reg:    CALLU1(addr)    "^JSR %0\n" 2
reg:    CALLP1(addr)    "^JSR %0\n" 2
stmt:   CALLV(addr)     "^JSR %0\n" 2

stmt:   RETF1(bval) "# return float\n" 2
stmt:   RETI1(bval) "# return int\n" 2
stmt:   RETU1(bval) "# return uint\n" 2
stmt:   RETP1(bval) "# return ptr\n" 2

stmt:   JUMPV(addr) "SET PC, %0\n" 1

stmt:   LABELV  ":%a\n"

%%

static void progbeg(int argc, char *argv[]) {
    {
        union {
            char c;
            int i;
        } u;
        u.i = 0;
        u.c = 1;
        swap = ((int)(u.i == 1)) != IR->little_endian;
    }
    parseflags(argc,argv);

    //put both ints and floats into IREG set
    reg[RGA] = mkreg("A",RGA,1,IREG);
    reg[RGB] = mkreg("B",RGB,1,IREG);
    reg[RGC] = mkreg("C",RGC,1,IREG);
    reg[RGI] = mkreg("I",RGI,1,IREG);
    reg[RGX] = mkreg("X",RGX,1,IREG);
    reg[RGY] = mkreg("Y",RGY,1,IREG);
    reg[RGZ] = mkreg("Z",RGZ,1,IREG);
    
    regw = mkwildcard(reg);
    
    tmask[IREG] = TMP_REG;
    vmask[IREG] = VAR_REG;
    tmask[FREG] = 0;
    vmask[FREG] = 0;

    print(";\n;DCPU-16 ASM Generated by LCC 4.2 (dcpu-lcc v0.1)\n;\n");
    print("JSR _main\n");
    print(":__crash SET PC, __crash\n");
}

static Symbol rmap(int opk) {
    switch (optype(opk)) {
    case B:
    case P:
    case I:
    case U:
    case F:
        return regw;
    default:
        return 0;
    }
}

static void segment(int n) {
}

static void progend(void) {
}

static void target(Node p) {
    debug(fprintf(stderr, "target called on %s\n", opname(p->op)));
    assert(p);
    switch (specific(p->op)) {
        case RET+F:
        case RET+I:
        case RET+U:
        case RET+P:
            rtarget(p, 0, reg[RGA]);
            break;
        case CALL+F:
        case CALL+I:
        case CALL+U:
        case CALL+P:
            setreg(p, reg[RGA]);
            break;        
    }
}

static void clobber(Node p) {
}

int memop(Node p) {
}

int sametree(Node p, Node q) {
}

static void emit2(Node p) {
    int localoffset;
    int argoffset;

    int op = specific(p->op); 
    if (opsize(p->op) == 1) {
        switch(op) {
            case ARG+F:
            case ARG+I:
            case ARG+U:
            case ARG+P:
                break;
            case CALL+F:
            case CALL+I:
            case CALL+U:
            case CALL+P:
                argoffset = p->syms[0]->u.c.v.i;
                //pop stack args
                popstack(argoffset);
                break;
            case ADDRL+P:
                localoffset = p->syms[0]->x.offset + maxoffset;
                if ( localoffset )
                    print("%d+J", localoffset);
                else
                    print("J");
                break;
            case ADDRF+P:
                print("%d+J", p->syms[0]->x.offset);
                break;
        }
    }
    else {
        //TODO ;)
    }
}

static void doarg(Node p) {
    assert(p && p->syms[0]);
    debug(fprintf(stderr, "doarg called %ld\n", p->syms[0]->u.c.v.i));
    mkactual(1, p->syms[0]->u.c.v.i);
    debug(fprintf(stderr, "doarg done with argoffset=%d\n", argoffset));
}

static void blkfetch(int k, int off, int reg, int tmp) {}
static void blkstore(int k, int off, int reg, int tmp) {}
static void blkloop(int dreg, int doff, int sreg, int soff,int size, int tmps[]) {}

static void local(Symbol p) {
    debug(fprintf(stderr, "local called on '%s'\n", p->name));
    if (askregvar(p,(*IR->x.rmap)(ttob(p->type)))==0) {
        mkauto(p);
    }
}

static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {
    int i,nreg,nfreg,nargs;
    long fused;
    Symbol fs;
    
    usedmask[IREG] = 0;
    usedmask[FREG] = 0;
    freemask[IREG] = TMP_REG | VAR_REG;
    freemask[FREG] = 0;

    maxargoffset = 0;
    offset = maxoffset = 0;

    for (i=0; callee[i]; i++) {
        Symbol p = callee[i];
        Symbol q = caller[i];
        assert(q);
        p->x.offset = q->x.offset = offset;
        p->x.name = q->x.name = stringf("%d",p->x.offset);
        p->sclass = q->sclass = AUTO;
        offset += roundup(q->type->size,q->type->align);
    }

    debug(fprintf(stderr, "function: calling gencode\n"));

    gencode(caller, callee);

    offset = maxoffset + 2;
    if (f->type->size > 1) {
        offset += f->type->size;
    }

    for (i=0; callee[i]; i++) {
        Symbol p = callee[i];
        Symbol q = caller[i];
        assert(q);
        p->x.offset = q->x.offset = offset;
        p->x.name = q->x.name = stringf("%d",p->x.offset);
        p->sclass = q->sclass = AUTO;
        offset += roundup(q->type->size,q->type->align);
    }

    // prologue
    print(":_%s ;maxoffset: %d maxargoffset: %d\n", f->name, maxoffset, maxargoffset);
    print("SET PUSH, J\n");

    //push locals
    pushstack(maxoffset);

    print("SET J, SP\n");

    emitcode();

    //epilogue

    //pop locals
    popstack(maxoffset);

    print("SET J, POP\n");
    print("SET PC, POP\n");
}

static void defsymbol(Symbol p) {
    if (p->scope >= LOCAL && p->sclass == STATIC)
        p->x.name = stringf("L%d", genlabel(1));
    else if (p->generated)
        p->x.name = stringf("L%s", p->name);
    else if (p->scope == GLOBAL || p->sclass == EXTERN)
        p->x.name = stringf("_%s",p->name);
    else if (p->scope == CONSTANTS && (isint(p->type) || isptr(p->type)) && p->name[0] == '0' && p->name[1] == 'x')
        p->x.name = stringf("0%sH", &p->name[2]);
    else
        p->x.name = p->name;
}

static void address(Symbol q, Symbol p, long n) {
        if (p->scope == GLOBAL || p->sclass == STATIC || p->sclass == EXTERN)
                q->x.name = stringf("%s%s%D", p->x.name, n >= 0 ? "+" : "", n);
        else {
                assert(n <= INT_MAX && n >= INT_MIN);
                q->x.offset = p->x.offset + n;
                q->x.name = stringd(q->x.offset);
        }
}

static void defconst(int suffix, int size, Value v) {
        print("\tDWM 0x%x\n",v.i & 0xffff);
}
static void defaddress(Symbol p) {
        print("\tDWM\t%s\n", p->x.name);
}

static void defstring(int n, char *str) {
    char *s=str;
    int first = 1;
    int quote = 0;
    print("\tDFB\t");
    while (s < str+n) {
        if ((*s >= ' ')&&(*s != '"')) {
           if (quote) {
              print("%c",*s++);
           } else {
               if (!first) {
                   print(",");
               }

          first = 0;
              print("\"%c",*s++);
          quote = 1;
           }
         } else {
            if (quote) {
             print("\",%d",*s++);
                 quote = 0;
            } else {
               if (!first) {
               first = 0;
                   print(",");
               }
             print("%d",*s++);
         first = 0;
         }
           
        }
    }
    printf("\n");
}

static void export(Symbol p) {
    debug(fprintf(stderr, "export called\n"));
}

static void import(Symbol p) {
    debug(fprintf(stderr, "import called\n"));
}

static void global(Symbol p) {
    //assert(p->type->align == 1);
    print(":%s\n", p->x.name);
}

static void space(int n) {
    print(";.space %d\n", n);
}

static void pushstack(int n) {
    if (n > 1)
        print("SUB SP, %d\n", n);
    else if (n == 1)
        print("SET PUSH, 0\n");
}

static void popstack(int n) {
    if (n > 2)
        print("ADD SP, %d\n", n);
    else if (n == 2)
        print("SET POP, POP\n", n);
    else if (n == 1)
        print("SET POP, SP\n");
}

Interface dcpu16IR = {
        1, 1, 0,  /* char */
        1, 1, 0,  /* short */
        1, 1, 0,  /* int */
        1, 1, 0,  /* long */
        1, 1, 0,  /* long long */
        1, 1, 0,  /* float */
        1, 1, 0,  /* double */
        1, 1, 0,  /* long double */
        1, 1, 0,  /* T * */
        0, 1, 0,  /* struct */
        0,        /* little_endian */
        1,        /* mulops_calls */
        0,        /* wants_callb */
        0,        /* wants_argb */
        0,        /* left_to_right */
        0,        /* wants_dag */
        1,        /* unsigned_char */
//        16,       /* byte width */
        address,
        blockbeg,
        blockend,
        defaddress,
        defconst,
        defstring,
        defsymbol,
        emit,
        export,
        function,
        gen,
        global,
        import,
        local,
        progbeg,
        progend,
        segment,
        space,
        0, 0, 0, 0, 0, 0, 0,
        {1, rmap,
            blkfetch, blkstore, blkloop,
            _label,
            _rule,
            _nts,
            _kids,
            _string,
            _templates,
            _isinstruction,
            _ntname,
            emit2,
            doarg,
            target,
            clobber,
}
};
static char rcsid[] = "$Id: $";
