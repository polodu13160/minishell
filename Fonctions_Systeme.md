# Documentation des Fonctions Système et Bibliothèques C

## Sommaire
1. [Fonctions de Lecture et d'Écriture](#fonctions-de-lecture-et-décriture)
2. [Gestion des Processus](#gestion-des-processus)
3. [Signaux](#signaux)
4. [Fichiers et Répertoires](#fichiers-et-répertoires)
5. [Terminal et Environnement](#terminal-et-environnement)
6. [Fonctions de la Bibliothèque Readline](#fonctions-de-la-bibliothèque-readline)

---

## 1. Fonctions de Lecture et d'Écriture

### `read`
**Description** : Lit des données depuis un descripteur de fichier.  
**Prototype** :
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
**Arguments** :
- `fd` : Descripteur de fichier à lire.
- `buf` : Buffer où stocker les données lues.
- `count` : Nombre d'octets à lire.

**Valeur de retour** :
- Nombre d'octets lus en cas de succès.
- `-1` en cas d'erreur.

**Exemple** :
```c
char buffer[128];
int bytes_read = read(0, buffer, sizeof(buffer)); // Lecture depuis stdin
```

---

### `write`
**Description** : Écrit des données dans un descripteur de fichier.  
**Prototype** :
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
**Arguments** :
- `fd` : Descripteur de fichier où écrire.
- `buf` : Données à écrire.
- `count` : Nombre d'octets à écrire.

**Valeur de retour** :
- Nombre d'octets écrits en cas de succès.
- `-1` en cas d'erreur.

**Exemple** :
```c
const char *msg = "Hello, world!\n";
write(1, msg, strlen(msg)); // Écriture sur stdout
```

---

## 2. Gestion des Processus

### `fork`
**Description** : Crée un nouveau processus en dupliquant le processus appelant.  
**Prototype** :
```c
#include <unistd.h>
pid_t fork(void);
```
**Valeur de retour** :
- `0` dans le processus fils.
- PID du fils dans le processus parent.
- `-1` en cas d'échec.

**Exemple** :
```c
pid_t pid = fork();
if (pid == 0) {
    printf("Processus fils\n");
} else {
    printf("Processus parent\n");
}
```

---

### `execve`
**Description** : Remplace l'image du processus courant par un nouveau programme.  
**Prototype** :
```c
#include <unistd.h>
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
**Arguments** :
- `pathname` : Chemin de l'exécutable.
- `argv` : Tableau des arguments.
- `envp` : Tableau des variables d’environnement.

**Valeur de retour** :
- Ne retourne jamais en cas de succès.
- `-1` en cas d'erreur.

**Exemple** :
```c
char *args[] = {"/bin/ls", "-l", NULL};
execve("/bin/ls", args, NULL);
```

---

## 3. Signaux

### `kill`
**Description** : Envoie un signal à un processus.  
**Prototype** :
```c
#include <signal.h>
int kill(pid_t pid, int sig);
```
**Arguments** :
- `pid` : PID du processus cible.
- `sig` : Signal à envoyer.

**Valeur de retour** :
- `0` en cas de succès.
- `-1` en cas d'erreur.

**Exemple** :
```c
kill(1234, SIGTERM); // Tue le processus 1234
```

---

### `signal`
**Description** : Définit un gestionnaire de signal.  
**Prototype** :
```c
#include <signal.h>
void (*signal(int signum, void (*handler)(int)))(int);
```
**Arguments** :
- `signum` : Signal à gérer.
- `handler` : Fonction appelée lors de la réception du signal.

**Exemple** :
```c
void handle_sigint(int sig) {
    printf("CTRL+C capturé !\n");
}

signal(SIGINT, handle_sigint);
```

---

## 4. Fichiers et Répertoires

### `open`
**Description** : Ouvre un fichier.  
**Prototype** :
```c
#include <fcntl.h>
int open(const char *pathname, int flags, mode_t mode);
```
**Exemple** :
```c
int fd = open("fichier.txt", O_RDONLY);
```

---

### `close`
**Description** : Ferme un descripteur de fichier.  
**Prototype** :
```c
#include <unistd.h>
int close(int fd);
```

---

## 5. Terminal et Environnement

### `getenv`
**Description** : Obtient la valeur d’une variable d’environnement.  
**Prototype** :
```c
#include <stdlib.h>
char *getenv(const char *name);
```
**Exemple** :
```c
printf("HOME = %s\n", getenv("HOME"));
```

---

## 6. Fonctions de la Bibliothèque Readline

### `readline`
**Description** : Lit une ligne de l’entrée standard avec édition interactive.  
**Prototype** :
```c
#include <readline/readline.h>
char *readline(const char *prompt);
```
**Exemple** :
```c
char *input = readline(">> ");
```

---

Fin de la documentation.
