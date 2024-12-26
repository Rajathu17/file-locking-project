#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// Admin credentials
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

// Function prototypes
void authenticate(GtkWidget *widget, gpointer data);
void lock_file(GtkWidget *widget, gpointer data);
void view_log(GtkWidget *widget, gpointer data);
void read_only_mode(GtkWidget *widget, gpointer data);

// File for locking
char file_name[100] = {0};

// Main function
int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *login_label, *username_entry, *password_entry, *login_button;

    gtk_init(&argc, &argv);

    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "File Lock System");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Add login widgets
    login_label = gtk_label_new("Admin Login");
    gtk_grid_attach(GTK_GRID(grid), login_label, 0, 0, 2, 1);

    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_grid_attach(GTK_GRID(grid), username_entry, 0, 1, 2, 1);

    password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Hide password
    gtk_grid_attach(GTK_GRID(grid), password_entry, 0, 2, 2, 1);

    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(authenticate), window);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 3, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

// Authenticate admin
void authenticate(GtkWidget *widget, gpointer data) {
    GtkWidget *window = (GtkWidget *)data;
    const char *username = gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), 0, 1)));
    const char *password = gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(window))), 0, 2)));

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        GtkWidget *file_window, *grid, *file_entry, *lock_button, *log_button, *readonly_button;

        gtk_widget_destroy(window);

        // Create new window for file operations
        file_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(file_window), "File Operations");
        gtk_window_set_default_size(GTK_WINDOW(file_window), 400, 200);
        g_signal_connect(file_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(file_window), grid);

        file_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(file_entry), "Enter File Name");
        gtk_grid_attach(GTK_GRID(grid), file_entry, 0, 0, 2, 1);

        lock_button = gtk_button_new_with_label("Lock File");
        g_signal_connect(lock_button, "clicked", G_CALLBACK(lock_file), file_entry);
        gtk_grid_attach(GTK_GRID(grid), lock_button, 0, 1, 2, 1);

        log_button = gtk_button_new_with_label("View Audit Log");
        g_signal_connect(log_button, "clicked", G_CALLBACK(view_log), NULL);
        gtk_grid_attach(GTK_GRID(grid), log_button, 0, 2, 2, 1);

        readonly_button = gtk_button_new_with_label("Read-Only Mode");
        g_signal_connect(readonly_button, "clicked", G_CALLBACK(read_only_mode), file_entry);
        gtk_grid_attach(GTK_GRID(grid), readonly_button, 0, 3, 2, 1);

        gtk_widget_show_all(file_window);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_CLOSE,
            "Invalid credentials! Please try again.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Lock file
void lock_file(GtkWidget *widget, gpointer data) {
    GtkWidget *file_entry = (GtkWidget *)data;
    const char *filename = gtk_entry_get_text(GTK_ENTRY(file_entry));
    if (strlen(filename) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_CLOSE,
            "File name cannot be empty!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Perform lock operation (call external C function or logic)
    snprintf(file_name, sizeof(file_name), "./file_lock %s 1", filename);
    system(file_name);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "File locked successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// View audit log
void view_log(GtkWidget *widget, gpointer data) {
    system("cat audit_log.txt");
}

// Read-only mode
void read_only_mode(GtkWidget *widget, gpointer data) {
    GtkWidget *file_entry = (GtkWidget *)data;
    const char *filename = gtk_entry_get_text(GTK_ENTRY(file_entry));
    if (strlen(filename) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_CLOSE,
            "File name cannot be empty!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    snprintf(file_name, sizeof(file_name), "./file_lock %s 3", filename);
    system(file_name);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "File set to read-only mode!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}