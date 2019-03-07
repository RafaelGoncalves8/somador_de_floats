/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>

/* Max number of chars in each float number in input. */
#define MAX 100

/* Error message and number in case of there is no space in memory. */;
#define NUM_ERR_OUT_OF_MEM -1
#define STR_ERR_OUT_OF_MEM "Nao ha espaco na memoria.\n"

/* Possible states of finite state machine. */
enum state
{
  INIT,
  CHAR,
  INT,
  FRAC,
  END
};

/* Finite state machine struct. */
typedef struct fsm
{
  int state;
}
Fsm;

typedef Fsm * fsm_ptr;

/* Return 1 if c is digit, 0 otherwise. */
int
is_digit(char c)
{
  if ((c >= '0') && (c <= '9'))
    return 1;
  else
    return 0;
}

/* Allocate memory for fsm. */
fsm_ptr
create_fsm()
{
  fsm_ptr machine;

  machine = (fsm_ptr) malloc(sizeof(Fsm));
  if (machine == NULL)
  {
    printf(STR_ERR_OUT_OF_MEM);
    exit(NUM_ERR_OUT_OF_MEM);
  }
  machine->state = INIT;

  return machine;
}

/* Change state of fsm based on input c and current state. */
void
operate_fsm(void * this_fsm, char c)
{
  fsm_ptr machine = (fsm_ptr) this_fsm;

  switch (machine->state)
  {
    case INIT:
      if (is_digit(c))
        machine->state = INT;
      else if (c != ' ' && c != '\n')
        machine->state = CHAR;
      break;

    case CHAR:
      if (c == ' ')
        machine->state = INIT;
      break;

    case INT:
      if (!is_digit(c))
      {
        if (c == '.')
          machine->state = FRAC;
        else if (c == ' ' || c == '\n')
          machine->state = END;
        else
          machine->state = INIT;
      }
      break;

    case FRAC:
      if (!is_digit(c))
      {
        if (c == ' ' || c == '\n')
          machine->state = END;
        else
          machine->state = CHAR;
      }
      break;

    case END:
      if (is_digit)
        machine->state = INT;
      else if (c != ' ' && c != '\n')
        machine->state = INIT;
      break;
  }
}

/* Free memory from fsm. */
void
destroy_fsm(fsm_ptr machine)
{
  free(machine);
}

/* Return empty buffer of char. */
void
clear_buffer(char * buffer)
{
  int i;

  for (i = 0; i < MAX; i++)
    buffer[i] = '\0';
}

int main() {
  double acc; /* Accumulates the total sum. */
  int i;
  char c, buffer[MAX];
  fsm_ptr machine;

  machine = create_fsm();

  acc = 0;
  i = 0;
  do
  {
    c = getchar();
    operate_fsm(machine, c);
    if (machine->state == INT || machine->state == FRAC)
    {
      buffer[i++] = c;
    }
    else if (machine->state == END)
    {
      acc += atof(buffer);
      clear_buffer(buffer);
      i = 0;
    }
    else /* fsm is in the init position. */
    {
      clear_buffer(buffer);
      i = 0;
    }
#if DEBUG
    printf("machine->state: %d\n", machine->state);
    printf("acc: %f\n", acc);
    printf("buffer: %s\n", buffer);
    printf("i: %d\n", i);
#endif
  }
  while (c != '\n'); /* Stop if c is \n. */

  printf("%g\n", acc);

  destroy_fsm(machine);

  return 0;
}
