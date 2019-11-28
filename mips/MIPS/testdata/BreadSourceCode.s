    .text
main:
  li $8, 4
  li $9, 5
  add $10, $8, $9
  add $a0, $zero, $10
  li $v0, 1
  syscall
  li $v0, 10
  syscall
