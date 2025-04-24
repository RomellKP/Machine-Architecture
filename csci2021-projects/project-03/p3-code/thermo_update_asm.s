# movb $5, %r9b # random code so hybrid runs
### Begin with functions/executable code in the assmebly file via '.text' directive
/text
.global  set_temp_from_ports
        
## ENTRY POINT FOR REQUIRED FUNCTION
set_temp_from_ports:
        # compares thermo sensor port to 0
        cmpw $0,THERMO_SENSOR_PORT(%rip)
        jl .ERROR

        # compares thermo sensor port to 28800
        cmpw $28800, THERMO_SENSOR_PORT(%rip)
        jg .ERROR


# takes thermo status port and copies value into some register
# uses & operator on the number w/4
# then compares compied number w/4
# jumps to error if the numbers are equal bc the 2nd bit determines error
# thermo status port value in cl at start
# 4 or 0 in cl at end
        movb THERMO_STATUS_PORT(%rip), %cl
        andb $4, %cl
        cmpb $4, %cl
        je .ERROR

# moves copy of thermo sensor port into dx and divides by 32
# %dx is bit_temp
        movw THERMO_SENSOR_PORT(%rip), %dx
        sarw $5, %dx 

# moves copy of thermo sensor port into si
# jumps if < 16 else adds 1 to bit_temp
        movw THERMO_SENSOR_PORT(%rip), %si
        andw $0b00011111, %si
        cmpw $16, %si
        jl .SMALLREMAIN
        addw $1, %dx

# new section after jump
# subtracts 450 from bit_temp and clears r8 register
.SMALLREMAIN:
        subw $450, %dx

# makes copy of thermo status port into 
# checks the fifth bit and if equal to 1 jumps to .fahrenheit
        movb THERMO_STATUS_PORT(%rip), %cl
        andb $32, %cl
        cmpb $32, %cl
        je .FAHRENHEIT

# moves bit_temp into tenths degrees
# moves 1 into temp mode then returns
        movw %dx, (%rdi)
        movb $1, 2(%rdi)
        movq $0, %rax
        movl $0, %eax
        ret

# new section multiplies by 9, moves dx into ax register
# coverts it to 32 bit in eax
# divides by 5 then adds 320
.FAHRENHEIT:
        movq $0, %r8
        movq $0, %rax
        imulw $9, %dx
        movw %dx, %ax
        cwtl
        cltq
        cqto
        movl $5, %r8d
        idivl %r8d
        addl $320, %eax

# moves new bit_temp in eax into rdi (tenths degree)
# moves 0 into temp mode and then returns
        movl %eax, (%rdi)
        movb $2, 2(%rdi)
        movq $0, %rax
        movl $0, %eax
        ret

# divider needs to be in eax and remainder goes into edx
# a useful technique for this problem
# movX    SOME_GLOBAL_VAR(%rip), %reg  # load global variable into register
                                             # use movl / movq / movw / movb
                                             # and appropriately sized destination register

# error function# 
.ERROR:
        movq $0, %rax
        movw $0, (%rdi)
        movb $3, 2(%rdi)
        movq $0, %rax
        movl $1, %eax
        ret                   # eventually return from the function




### Change to definine semi-global variables used with the next function 
### via the '.data' directive
.data
	
an_int:                         # declare location an single integer named 'an_int'
        .int 1234               # value 1234

other_int:                      # declare another int accessible via name 'other_int'
        .int 0b0101             # binary value as per C
# in order: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, negative sign, blank, E, R
an_array:                       # declare multiple ints sequentially starting at location
        .int 0b1111011                  # 'an_array' for an array. Each are spaced 4 bytes from the
        .int 0b1001000             # next and can be given values using the same prefixes as 
        .int 0b0111101            # are understood by gcc.
        .int 0b1101101
        .int 0b1001110
        .int 0b1100111
        .int 0b1110111
        .int 0b1001001
        .int 0b1111111
        .int 0b1101111
        .int 0b0000100
        .int 0b0000000
        .int 0b0110111
        .int 0b1011111


### Change back to defining functions/execurable instructions
.text
.global  set_display_from_temp

## ENTRY POINT FOR REQUIRED FUNCTION
set_display_from_temp:  
# zero out registers and moves total into r8
        movq $0, %rdx
        movq $0, %rcx
        movq $0, %r9
        movq $0, %r8
        movl 1(%rdi), %r8d

# this is num_display in r9
        movq $0, %r9
        movl $0, %r9d

# error check if temp.temp_mode != 1 and 2
# moves 0 into r11, and compares rdx with 1
# adds 1 r11 if equal and if not jumps
        movq $0, %r11
        movq $1, %rdx
        cmpq %rdx, 2(%rdi)
        je .NOMODEERROR
        addq $1, %r11

# moves 2 into rdx and compares 2 with the temp_mode
# adds 1 to r11 if equal and if not jumps
# jumps to error if r11 == 2
        movq $2, %rdx
        cmpq %rdx, 2(%rdi)
        je .NOMODEERROR
        addq $1, %r11
        cmpq $2, %r11
        je .ERROR

.NOMODEERROR:
# check for which mode and if not fahrenheight does celsius check
# jumps to error if out of range otherwise jumps past fahrenheight check
        movq $0, %r11
        cmpq $2, %rdx
        je .FRANCHECK
        movq $-450, %r11
        movq $450, %rdx
        cmpq %rdx, 1(%rdi)
        jg .ERROR
        cmpq %r11, 1(%rdi)
        jl .ERRORDISPLAY
        jmp .PASTCHECK

# does same as celsius check but with fahrenheight range
.FRANCHECK:
        movq $-490, %r11
        movq $1130, %rdx
        cmpq %rdx, 1(%rdi)
        jg .ERRORDISPLAY
        cmpq %r11, 1(%rdi)
        jl .ERRORDISPLAY

.PASTCHECK:
# now check for negative value
# is_neg will be in r11 so I need to zero out
# or with promer mask neg sign and shift 7 to left
        movq $0, %r11
        movq $0, %rdx
        cmpq %r11, %r8
        jg .NOTNEG
        leaq an_array(%rip), %r11
        movq $10, %rdx
        movl (%r11, %rdx, 4), %r10d
        orl %r10d, %r9d
        sall $7, %r9d
        imulq $-1, %r8
        movq $1, %r11


.NOTNEG:
# rdx will be temp_tenths
        movq $99, %rdx
        movw %r8w, %ax
        cmpq $1, %r11
        je .TENTHSNEG
        movq $0, %rdx
        movw %r8w, %ax
        cwtl
        cltq
        cqto
        movl $10, %r10d
        idivl %r10d
        movq $0, %r8
        movw %ax, %r8w
# r8d is now total and rdx is temp_tenths
# tenths neg cwtl, cwtq, cqto remainder stored in edx

# r8-total, r9-num_display, rdx-temp_tenths, rest are open to be used
# temp_tenths should be in rdx but are moved to rcx
.TENTHSNEG:
# this is for ones and will be moved from rdx to r10
        movq %rdx, %rcx
        movw %r8w, %ax
        cwtl
        cltq
        cqto
        movl $10, %r10d
        idivl %r10d
        movq $0, %r8
        movw %ax, %r8w
        movq %rdx, %r10

# this is for tens and will be moved into r11
        movw %r8w, %ax
        cwtl
        cltq
        cqto
        movl $10, %r10d
        idivl %r10d
        movq $0, %r8
        movw %ax, %r8w
        movq %rdx, %r11

# this is for hundreds and will stay in rdx
        movw %r8w, %ax
        cwtl
        cltq
        cqto
        movl $10, %r10d
        idivl %r10d
        movq $0, %r8
        movw %ax, %r8w

# no longer need total so r8 will be used to get address of start of the array
# check hundreds != 0
        cmpq $0, %rdx
        je .EQUALH
        leaq an_array(%rip), %r8
        movl (%r8, %rdx, 4), %eax
        orl %eax, %r9d
        sall $7, %r9d

# check tens
.EQUALH:
        cmpq $0, %r11
        je .EQUALTENS
        movl (%r8, %r11, 4), %eax
        orl %eax, %r9d
        sall $7, %r9d

# check ones
.EQUALTENS:
        cmpq $0, %r10
        je .EQUALONES
        movl (%r8, %r10, 4), %eax
        orl %eax, %r9d
        sall $7, %r9d

# check tenths
.EQUALONES:
        cmpq $99, %rcx
        je .EQUALTENTHS
        movl (%r8, %rcx, 4), %eax
        orl %eax, %r9d
        sall $7, %r9d

# now all we need is r9 as num_display so zero out other registers
# cf_mask will be in r11
# num_places will be in r10
.EQUALTENTHS:
        movq $0, %rdx
        movq $0, %rcx
        movq $0, %rax
        movq $0, %r8
        movq $0, %r10
        movq $1, %r11
        movq 2(%rdi), %rcx
        cmpq $1, %rcx
        jne .NOTEQUALMODE
        movb $28, %cl

.NOTEQUALMODE:
        movb $29, %cl
# shifts cf_mask left by r10 places and ors it with r9

        sal %cl, %r11d
        orl %r11d, %r9d
        movl %r9d, (%edi)
        movq $0, %rax
        ret


.ERRORDISPLAY:
# or with the proper mask E and shift 7 to left
        leaq an_array(%rip), %r8
        movq $12, %rcx
        movl (%r8,%rcx, 4), %r10d
        orl %r10d, %r9d
        sall $7, %r9d

# or with proper mask R and shift 7 to left
        movq $13, %rcx
        movl (%r8,%rcx, 4), %r10d
        orl %r10d, %r9d
        sall $7, %r9d

# or with proper mask R and shift 7 to left
        movq $13, %rcx
        movl (%r8,%rcx, 4), %r10d
        orl %r10d, %r9d
        sall $7, %r9d

# or with proper mask blank
        movq $11, %rcx
        movl (%r8,%rcx, 4), %r10d
        orl %r10d, %r9d

# make edi equal to r9d
        movl %r9d, (%edi)
        movq $1, %rax
        ret
	/*## two useful techniques for this problem
        movl    an_int(%rip),%eax    # load an_int into register eax
        leaq    an_array(%rip),%rdx  # load pointer to beginning of an_array into edx
        
        ret                     # eventually return from the function*/

/*.text
.global thermo_update
        
## ENTRY POINT FOR REQUIRED FUNCTION
thermo_update:
	## assembly instructions here

        ret*/                     # eventually return from the function
