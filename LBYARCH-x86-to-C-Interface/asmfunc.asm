section .text
bits 64
default rel

global runSAXPYInNASM
extern printf

; n = rcx
; A = xmm1
; X = r8
; Y = r9
; Z = rsp + 40 (r10)

; i = r11

runSAXPYInNASM:
	; r10 = *Z
	MOV r10, [rsp + 40]

	; i = 0
	XOR r11, r11

L1:
	; xmm0 = X[i]
	MOVSS xmm0, [r8 + r11 * 4]

	; xmm0 = A (xmm1) * X[i] (xmm0)
	MULSS xmm0, xmm1

	; xmm0 += Y[i] (r9 + i * 4)
	ADDSS xmm0, [r9 + r11 * 4]

	; Z[i] = xmm0
	MOVSS [r10 + r11 * 4], xmm0

	; i++
	ADD r11, 1

	; Loop n (rcx) times
	LOOP L1

	xor rax, rax
	ret