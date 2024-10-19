

#include "commands.hpp"
#include <cstdlib>


void Commands::openFacebook(){
    // Open Facebook
    system("xdg-open https://www.facebook.com");
}

void Commands::openYoutube(){
    // Open YouTube
    system("xdg-open https://www.youtube.com");
}

void Commands::openWhatsapp(){
     // Open WhatsApp Web
    system("xdg-open https://web.whatsapp.com");
}

void Commands::openLinkedin(){
    // Open LinkedIn
    system("xdg-open https://www.linkedin.com");
}

void Commands::openGithub(){
    // Open GitHub
    system("xdg-open https://github.com");
}

void Commands::openCalculator(){
    // Open Calculator
    system("gnome-calculator");
}

void Commands::openVSCode(){
        // Open VS Code
    system("code .");
}

void Commands::openTelegram() {
    system("xdg-open https://web.telegram.org/");
}