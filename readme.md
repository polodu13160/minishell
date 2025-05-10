# Documentation des fonctions système en C

## Sommaire

- [Manipulation de l'entrée/sortie](#manipulation-de-lentréesortie)
  - [readline](#readline)
  - [rl_clear_history](#rl_clear_history)
  - [rl_on_new_line](#rl_on_new_line)
  - [rl_replace_line](#rl_replace_line)
  - [rl_redisplay](#rl_redisplay)
  - [add_history](#add_history)
  - [printf](#printf)
  - [write](#write)
  - [isatty](#isatty)
  - [ttyname](#ttyname)
  - [ttyslot](#ttyslot)
  - [ioctl](#ioctl)
  - [tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs](#tgetent-tgetflag-tgetnum-tgetstr-tgoto-tputs)
  - [tcsetattr, tcgetattr](#tcsetattr-tcgetattr)

- [Gestion de la mémoire](#gestion-de-la-mémoire)
  - [malloc](#malloc)
  - [free](#free)

- [Manipulation de fichiers](#manipulation-de-fichiers)
  - [access](#access)
  - [open](#open)
  - [read](#read)
  - [close](#close)
  - [unlink](#unlink)
  - [getcwd](#getcwd)
  - [chdir](#chdir)
  - [stat, lstat, fstat](#stat-lstat-fstat)

- [Gestion des processus](#gestion-des-processus)
  - [fork](#fork)
  - [wait, waitpid, wait3, wait4](#wait-waitpid-wait3-wait4)
  - [execve](#execve)
  - [exit](#exit)
  - [pipe](#pipe)
  - [dup, dup2](#dup-dup2)

- [Gestion des répertoires](#gestion-des-répertoires)
  - [opendir](#opendir)
  - [readdir](#readdir)
  - [closedir](#closedir)

- [Gestion des signaux](#gestion-des-signaux)
  - [signal](#signal)
  - [sigaction](#sigaction)
  - [sigemptyset](#sigemptyset)
  - [sigaddset](#sigaddset)
  - [kill](#kill)

- [Gestion des erreurs](#gestion-des-erreurs)
  - [strerror](#strerror)
  - [perror](#perror)

- [Variables d'environnement](#variables-denvironnement)
  - [getenv](#getenv)

---

## Manipulation de l'entrée/sortie

### readline

**Include:** `<readline/readline.h>`

**Prototype:**
```c
char *readline(const char *prompt);
```

**Description:**  
Lit une ligne depuis l'entrée standard avec gestion de l'édition. Affiche le prompt spécifié. La ligne renvoyée a le caractère de nouvelle ligne supprimé, et doit être libérée par l'appelant avec `free()`.

**Exemple:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main() {
    char *line;
    
    line = readline("Entrez une commande: ");
    if (line) {
        printf("Vous avez saisi: %s\n", line);
        free(line);
    }
    
    return 0;
}
```

### rl_clear_history

**Include:** `<readline/history.h>`

**Prototype:**
```c
void rl_clear_history(void);
```

**Description:**  
Efface la liste d'historique maintenue par la bibliothèque readline.

**Exemple:**
```c
#include <readline/history.h>

int main() {
    // Après utilisation de l'historique
    rl_clear_history();
    return 0;
}
```

### rl_on_new_line

**Include:** `<readline/readline.h>`

**Prototype:**
```c
int rl_on_new_line(void);
```

**Description:**  
Informe la bibliothèque readline que le curseur est passé à une nouvelle ligne. Utile lors de l'affichage de lignes de texte multiples.

**Exemple:**
```c
#include <readline/readline.h>

void afficher_texte() {
    printf("Texte sur plusieurs lignes\n");
    rl_on_new_line();  // Informe readline que nous sommes sur une nouvelle ligne
}
```

### rl_replace_line

**Include:** `<readline/readline.h>`

**Prototype:**
```c
void rl_replace_line(const char *text, int clear_undo);
```

**Description:**  
Remplace le contenu de la ligne courante par le texte spécifié. Si `clear_undo` est non nul, l'historique d'annulation est effacé.

**Exemple:**
```c
#include <readline/readline.h>

void remplacer_ligne() {
    rl_replace_line("Nouveau texte", 1);
    rl_redisplay();  // Affiche la ligne modifiée
}
```

### rl_redisplay

**Include:** `<readline/readline.h>`

**Prototype:**
```c
void rl_redisplay(void);
```

**Description:**  
Force le réaffichage de la ligne d'entrée actuelle.

**Exemple:**
```c
#include <readline/readline.h>

void modifier_et_afficher() {
    rl_replace_line("Texte modifié", 1);
    rl_redisplay();  // Actualise l'affichage
}
```

### add_history

**Include:** `<readline/history.h>`

**Prototype:**
```c
void add_history(const char *line);
```

**Description:**  
Ajoute la ligne spécifiée à l'historique de readline, permettant à l'utilisateur de rappeler cette ligne avec les touches fléchées.

**Exemple:**
```c
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;
    
    while ((line = readline("$ ")) != NULL) {
        if (*line) {  // Si la ligne n'est pas vide
            add_history(line);  // Ajoute à l'historique
            // Traitement de la ligne...
        }
        free(line);
    }
    
    return 0;
}
```

### printf

**Include:** `<stdio.h>`

**Prototype:**
```c
int printf(const char *format, ...);
```

**Description:**  
Formate et affiche des données sur la sortie standard selon le format spécifié.

**Exemple:**
```c
#include <stdio.h>

int main() {
    int age = 30;
    float taille = 1.75;
    
    printf("Age: %d ans, Taille: %.2f m\n", age, taille);
    
    return 0;
}
```

### write

**Include:** `<unistd.h>`

**Prototype:**
```c
ssize_t write(int fd, const void *buf, size_t count);
```

**Description:**  
Écrit jusqu'à `count` octets depuis le tampon pointé par `buf` vers le descripteur de fichier `fd`.

**Exemple:**
```c
#include <unistd.h>
#include <string.h>

int main() {
    const char *message = "Hello, world!\n";
    
    // Écrire sur la sortie standard (fd = 1)
    write(1, message, strlen(message));
    
    return 0;
}
```

### isatty

**Include:** `<unistd.h>`

**Prototype:**
```c
int isatty(int fd);
```

**Description:**  
Vérifie si le descripteur de fichier `fd` est associé à un terminal.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    if (isatty(STDOUT_FILENO)) {
        printf("La sortie standard est un terminal.\n");
    } else {
        printf("La sortie standard n'est pas un terminal.\n");
    }
    
    return 0;
}
```

### ttyname

**Include:** `<unistd.h>`

**Prototype:**
```c
char *ttyname(int fd);
```

**Description:**  
Renvoie un pointeur vers une chaîne contenant le nom du terminal associé au descripteur de fichier `fd`, ou NULL si `fd` n'est pas un terminal.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *tty_name = ttyname(STDIN_FILENO);
    
    if (tty_name) {
        printf("Nom du terminal: %s\n", tty_name);
    } else {
        printf("L'entrée standard n'est pas un terminal.\n");
    }
    
    return 0;
}
```

### ttyslot

**Include:** `<unistd.h>`

**Prototype:**
```c
int ttyslot(void);
```

**Description:**  
Renvoie l'index de l'entrée actuelle du terminal dans le fichier `/etc/ttys`.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    int slot = ttyslot();
    
    if (slot != -1) {
        printf("Slot du terminal: %d\n", slot);
    } else {
        printf("Impossible de déterminer le slot du terminal.\n");
    }
    
    return 0;
}
```

### ioctl

**Include:** `<sys/ioctl.h>`

**Prototype:**
```c
int ioctl(int fd, unsigned long request, ...);
```

**Description:**  
Effectue des opérations de contrôle d'entrée/sortie sur un descripteur de fichier. Utilisé pour manipuler les paramètres des périphériques.

**Exemple:**
```c
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct winsize ws;
    
    // Récupérer les dimensions du terminal
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        printf("Dimensions du terminal: %d lignes x %d colonnes\n", 
               ws.ws_row, ws.ws_col);
    } else {
        perror("ioctl");
    }
    
    return 0;
}
```

### tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

**Include:** `<term.h>` ou `<curses.h>` et `<term.h>`

**Prototypes:**
```c
int tgetent(char *bp, const char *name);
int tgetflag(char *id);
int tgetnum(char *id);
char *tgetstr(char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
```

**Description:**  
Fonctions de la bibliothèque termcap pour accéder aux capacités du terminal:
- `tgetent`: Charge l'entrée termcap pour le terminal spécifié
- `tgetflag`: Récupère un drapeau booléen de la base de données termcap
- `tgetnum`: Récupère une valeur numérique de la base de données termcap
- `tgetstr`: Récupère une chaîne de capacité de la base de données termcap
- `tgoto`: Génère une chaîne pour déplacer le curseur
- `tputs`: Envoie une chaîne de contrôle au terminal

**Exemple:**
```c
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int putchar_wrapper(int c) {
    return putchar(c);
}

int main() {
    char term_buffer[2048];
    char *term_type = getenv("TERM");
    
    if (!term_type) {
        fprintf(stderr, "Variable TERM non définie\n");
        return 1;
    }
    
    // Initialiser termcap pour le type de terminal
    if (tgetent(term_buffer, term_type) != 1) {
        fprintf(stderr, "Terminal non trouvé dans la base termcap\n");
        return 1;
    }
    
    // Récupérer le nombre de colonnes
    int cols = tgetnum("co");
    printf("Le terminal a %d colonnes\n", cols);
    
    // Récupérer la capacité de déplacement du curseur
    char *cm = tgetstr("cm", (char **)NULL);
    if (cm) {
        // Déplacer le curseur à la position (10, 5)
        char *move_cmd = tgoto(cm, 10, 5);
        tputs(move_cmd, 1, putchar_wrapper);
        printf("Texte à la position (10,5)\n");
    }
    
    return 0;
}
```

### tcsetattr, tcgetattr

**Include:** `<termios.h>`

**Prototypes:**
```c
int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

**Description:**  
- `tcgetattr`: Récupère les paramètres du terminal associé au descripteur de fichier
- `tcsetattr`: Définit les paramètres du terminal associé au descripteur de fichier

**Exemple:**
```c
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct termios term, term_orig;
    
    // Sauvegarder les paramètres actuels
    tcgetattr(STDIN_FILENO, &term_orig);
    term = term_orig;
    
    // Désactiver l'écho des caractères
    term.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
    printf("Mode sans écho activé. Appuyez sur une touche...\n");
    char c = getchar();
    printf("Vous avez appuyé sur: %c\n", c);
    
    // Restaurer les paramètres originaux
    tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
    
    return 0;
}
```

## Gestion de la mémoire

### malloc

**Include:** `<stdlib.h>`

**Prototype:**
```c
void *malloc(size_t size);
```

**Description:**  
Alloue `size` octets de mémoire et renvoie un pointeur vers la mémoire allouée. La mémoire n'est pas initialisée.

**Exemple:**
```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Allouer de la mémoire pour une chaîne de caractères
    char *str = (char *)malloc(20);
    
    if (str == NULL) {
        fprintf(stderr, "Échec de l'allocation mémoire\n");
        return 1;
    }
    
    strcpy(str, "Hello, world!");
    printf("%s\n", str);
    
    // Libérer la mémoire
    free(str);
    
    return 0;
}
```

### free

**Include:** `<stdlib.h>`

**Prototype:**
```c
void free(void *ptr);
```

**Description:**  
Libère l'espace mémoire pointé par `ptr`, qui doit avoir été retourné par un appel antérieur à `malloc`, `calloc` ou `realloc`.

**Exemple:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Échec de l'allocation mémoire\n");
        return 1;
    }
    
    // Utiliser le tableau
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Libérer la mémoire
    free(arr);
    
    return 0;
}
```

## Manipulation de fichiers

### access

**Include:** `<unistd.h>`

**Prototype:**
```c
int access(const char *pathname, int mode);
```

**Description:**  
Vérifie les permissions d'accès de l'utilisateur pour le fichier spécifié. Les modes possibles sont:
- `R_OK`: Test de permission en lecture
- `W_OK`: Test de permission en écriture
- `X_OK`: Test de permission en exécution
- `F_OK`: Test d'existence du fichier

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "test.txt";
    
    if (access(filename, F_OK) == 0) {
        printf("Le fichier %s existe.\n", filename);
        
        if (access(filename, R_OK) == 0) {
            printf("Le fichier est lisible.\n");
        }
        
        if (access(filename, W_OK) == 0) {
            printf("Le fichier est modifiable.\n");
        }
        
        if (access(filename, X_OK) == 0) {
            printf("Le fichier est exécutable.\n");
        }
    } else {
        printf("Le fichier %s n'existe pas.\n", filename);
    }
    
    return 0;
}
```

### open

**Include:** `<fcntl.h>`

**Prototype:**
```c
int open(const char *pathname, int flags, mode_t mode);
```

**Description:**  
Ouvre le fichier spécifié et renvoie un descripteur de fichier. Les drapeaux (`flags`) peuvent inclure:
- `O_RDONLY`: Ouverture en lecture seule
- `O_WRONLY`: Ouverture en écriture seule
- `O_RDWR`: Ouverture en lecture et écriture
- `O_CREAT`: Créer le fichier s'il n'existe pas
- `O_APPEND`: Ajouter à la fin du fichier
- Autres options disponibles

Le paramètre `mode` définit les permissions du fichier lors de sa création (utilisé avec `O_CREAT`).

**Exemple:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    
    // Ouvrir un fichier en lecture/écriture, le créer s'il n'existe pas
    fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    printf("Fichier ouvert avec succès, descripteur: %d\n", fd);
    
    // Écrire dans le fichier
    const char *message = "Hello, world!\n";
    write(fd, message, 14);
    
    // Fermer le fichier
    close(fd);
    
    return 0;
}
```

### read

**Include:** `<unistd.h>`

**Prototype:**
```c
ssize_t read(int fd, void *buf, size_t count);
```

**Description:**  
Lit jusqu'à `count` octets du descripteur de fichier `fd` dans le tampon `buf`.

**Exemple:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read;
    
    // Ouvrir un fichier en lecture
    fd = open("test.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    // Lire depuis le fichier
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // Ajouter un caractère nul pour terminer la chaîne
    buffer[bytes_read] = '\0';
    
    printf("Contenu lu (%zd octets): %s\n", bytes_read, buffer);
    
    // Fermer le fichier
    close(fd);
    
    return 0;
}
```

### close

**Include:** `<unistd.h>`

**Prototype:**
```c
int close(int fd);
```

**Description:**  
Ferme un descripteur de fichier, libérant ainsi les ressources associées.

**Exemple:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    printf("Fichier ouvert, descripteur: %d\n", fd);
    
    // Utilisation du fichier...
    
    // Fermer le fichier
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    
    printf("Fichier fermé avec succès\n");
    
    return 0;
}
```

### unlink

**Include:** `<unistd.h>`

**Prototype:**
```c
int unlink(const char *pathname);
```

**Description:**  
Supprime un nom du système de fichiers. Si ce nom était le dernier lien vers un fichier et qu'aucun processus n'a le fichier ouvert, le fichier est supprimé.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    // Créer un fichier temporaire
    int fd = open("temp.txt", O_CREAT | O_WRONLY, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    write(fd, "Contenu temporaire", 18);
    close(fd);
    
    printf("Fichier temp.txt créé\n");
    
    // Supprimer le fichier
    if (unlink("temp.txt") == -1) {
        perror("unlink");
        return 1;
    }
    
    printf("Fichier temp.txt supprimé\n");
    
    return 0;
}
```

### getcwd

**Include:** `<unistd.h>`

**Prototype:**
```c
char *getcwd(char *buf, size_t size);
```

**Description:**  
Obtient le chemin du répertoire de travail courant. La chaîne est placée dans le tampon `buf` de taille `size`.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Répertoire de travail actuel: %s\n", cwd);
    } else {
        perror("getcwd");
        return 1;
    }
    
    return 0;
}
```

### chdir

**Include:** `<unistd.h>`

**Prototype:**
```c
int chdir(const char *path);
```

**Description:**  
Change le répertoire de travail courant du processus appelant pour le chemin spécifié.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char cwd[1024];
    
    // Afficher le répertoire actuel
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Répertoire initial: %s\n", cwd);
    }
    
    // Changer de répertoire
    if (chdir("/tmp") != 0) {
        perror("chdir");
        return 1;
    }
    
    // Vérifier le nouveau répertoire
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Nouveau répertoire: %s\n", cwd);
    }
    
    return 0;
}
```

### stat, lstat, fstat

**Include:** `<sys/stat.h>`

**Prototypes:**
```c
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
```

**Description:**  
- `stat`: Récupère les informations sur un fichier pointé par pathname
- `lstat`: Comme stat, mais si le fichier est un lien symbolique, renvoie les informations sur le lien lui-même
- `fstat`: Récupère les informations sur un fichier référencé par son descripteur

**Exemple:**
```c
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_file_info(const char *filename) {
    struct stat sb;
    
    if (stat(filename, &sb) == -1) {
        perror("stat");
        return;
    }
    
    printf("Informations sur le fichier '%s':\n", filename);
    printf("Taille: %lld octets\n", (long long)sb.st_size);
    printf("Permissions: %o\n", sb.st_mode & 0777);
    printf("Dernière modification: %s", ctime(&sb.st_mtime));
    
    printf("Type: ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("périphérique bloc\n");      break;
        case S_IFCHR:  printf("périphérique caractère\n"); break;
        case S_IFDIR:  printf("répertoire\n");             break;
        case S_IFIFO:  printf("FIFO/tube\n");              break;
        case S_IFLNK:  printf("lien symbolique\n");        break;
        case S_IFREG:  printf("fichier ordinaire\n");      break;
        case S_IFSOCK: printf("socket\n");                 break;
        default:       printf("inconnu\n");                break;
    }
}

int main() {
    print_file_info("/etc/passwd");
    return 0;
}
```

## Gestion des processus

### fork

**Include:** `<unistd.h>`

**Prototype:**
```c
pid_t fork(void);
```

**Description:**  
Crée un nouveau processus en dupliquant le processus appelant. Le nouveau processus (enfant) est une copie exacte du processus parent, sauf pour certaines valeurs retournées par `fork()`.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Je suis le processus enfant (PID: %d, Parent: %d)
", getpid(), getppid());
    } else {
        printf("Je suis le processus parent (PID: %d, Enfant: %d)
", getpid(), pid);
        wait(NULL);
        printf("Le processus enfant s'est terminé
");
    }

    return 0;
}
```

### wait, waitpid, wait3, wait4

**Include:** `<sys/wait.h>`

**Prototype:**
```c
pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

**Description:**  
`wait` attend la fin d'un processus enfant. `waitpid` permet plus de contrôle (par exemple, attendre un PID spécifique).

**Exemple:**
```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Enfant (PID: %d)
", getpid());
        exit(42);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("L'enfant s'est terminé avec le code %d
", WEXITSTATUS(status));
    }
    return 0;
}
```

### execve

**Include:** `<unistd.h>`

**Prototype:**
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

**Description:**  
Remplace le processus courant par un nouveau programme.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *argv[] = {"/bin/ls", "-l", NULL};
    execve("/bin/ls", argv, NULL);
    perror("execve");
    return 1;
}
```

### exit

**Include:** `<stdlib.h>`

**Prototype:**
```c
void exit(int status);
```

**Description:**  
Termine le processus courant avec un code de retour.

**Exemple:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Fin du programme
");
    exit(0);
}
```

### pipe

**Include:** `<unistd.h>`

**Prototype:**
```c
int pipe(int pipefd[2]);
```

**Description:**  
Crée un canal de communication unidirectionnel entre deux processus.

**Exemple:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    char buffer[20];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    write(fd[1], "hello", 6);
    read(fd[0], buffer, sizeof(buffer));
    printf("Message: %s
", buffer);
    return 0;
}
```

### dup, dup2

**Include:** `<unistd.h>`

**Prototype:**
```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

**Description:**  
Duplique un descripteur de fichier. `dup2` permet de spécifier le descripteur de destination.

**Exemple:**
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1); // Redirige stdout vers le fichier
    printf("Ce message va dans le fichier
");
    close(fd);
    return 0;
}
```

## Gestion des répertoires

### opendir

**Include:** `<dirent.h>`

**Prototype:**
```c
DIR *opendir(const char *name);
```

**Description:**  
Ouvre un répertoire pour la lecture.

### readdir

**Include:** `<dirent.h>`

**Prototype:**
```c
struct dirent *readdir(DIR *dirp);
```

**Description:**  
Lit une entrée du répertoire ouvert.

### closedir

**Include:** `<dirent.h>`

**Prototype:**
```c
int closedir(DIR *dirp);
```

**Description:**  
Ferme un répertoire précédemment ouvert.

**Exemple pour les trois:**
```c
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s
", entry->d_name);
        }
        closedir(dir);
    }
    return 0;
}
```

## Gestion des signaux

### signal

**Include:** `<signal.h>`

**Prototype:**
```c
void (*signal(int sig, void (*handler)(int)))(int);
```

**Description:**  
Définit un gestionnaire pour un signal.

**Exemple:**
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal %d reçu
", sig);
}

int main() {
    signal(SIGINT, handler);
    while (1) pause();
    return 0;
}
```

### sigaction

**Include:** `<signal.h>`

**Prototype:**
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

**Description:**  
Permet une gestion avancée des signaux.

**Exemple:**
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal %d capturé
", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    kill(getpid(), SIGUSR1);

    return 0;
}
```

### sigemptyset / sigaddset

**Include:** `<signal.h>`

**Prototype:**
```c
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
```

**Description:**  
Initialise un ensemble vide de signaux et y ajoute des signaux.

**Exemple:**
```c
#include <signal.h>
#include <stdio.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    printf("SIGINT ajouté au set
");
    return 0;
}
```

### kill

**Include:** `<signal.h>`

**Prototype:**
```c
int kill(pid_t pid, int sig);
```

**Description:**  
Envoie un signal à un processus.

**Exemple:**
```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handler(int sig) {
    printf("Signal %d reçu
", sig);
}

int main() {
    signal(SIGUSR1, handler);
    kill(getpid(), SIGUSR1);
    return 0;
}
```

## Gestion des erreurs

### strerror

**Include:** `<string.h>`

**Prototype:**
```c
char *strerror(int errnum);
```

**Description:**  
Retourne un message d'erreur correspondant à un code d'erreur.

### perror

**Include:** `<stdio.h>`

**Prototype:**
```c
void perror(const char *s);
```

**Description:**  
Affiche un message d'erreur avec la description liée à errno.

**Exemple pour les deux:**
```c
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *f = fopen("inexistant.txt", "r");
    if (!f) {
        perror("fopen");
        printf("strerror: %s
", strerror(errno));
    }
    return 0;
}
```

## Variables d'environnement

### getenv

**Include:** `<stdlib.h>`

**Prototype:**
```c
char *getenv(const char *name);
```

**Description:**  
Retourne la valeur d'une variable d'environnement.

**Exemple:**
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *home = getenv("HOME");
    if (home) {
        printf("HOME = %s
", home);
    }
    return 0;
}
```