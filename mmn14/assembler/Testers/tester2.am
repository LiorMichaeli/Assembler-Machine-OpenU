;tester2
; Errors in the amount of the operands in the line
mov A
mov
mov D, #
cmp A
cmp

; Errors in the commas in the line

and:  ,stop
mov ,, 2 , 2
add 2,, 9   

; Illegal operands

helo: cmp %8, #8		
easfsa: cmp #987, r3
add :8, *8
sub #8, @8

; Illegal data guidance and string guidance line

.data #8, 8, 12
.data 
.data 8.0
label: .data +-8
.string
.string ""
.string ,,asafak
.string "asfsaf
.string asfasfaf"

; Illegal third adress type

abc: jmp L1(#5, N)
 jmp 1L(#5,N)
 bne L!!@$(#5,#5)
 jsr L(1r,#5)
 bne L(
 
; Errors in extern and entry guidance

.extern
.entry
