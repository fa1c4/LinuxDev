// Import necessary items for file I/O
use std::fs::{File, OpenOptions};
use std::io::{Read, Write, ErrorKind};
use std::path::Path;

// Import Iced components
use iced::widget::{button, column, container, row, text};
use iced::{Alignment, Element, Length, Sandbox, Settings, Size};

// Define the filename for storing the counter value
const STATE_FILENAME: &str = "counter_state.txt";

// Helper function to load the value from the file
fn load_value_from_file() -> Option<i32> {
    // Check if the file exists first
    if !Path::new(STATE_FILENAME).exists() {
        match save_value_to_file(0) { // Try to save 0 to create the file
            Ok(_) => {
                // Successfully created and wrote 0 to the file.
                // The application will start with 0, and the file now exists.
                // println!("Info: Successfully created state file '{}' with value 0.", STATE_FILENAME); // For debugging
                return Some(0);
            }
            Err(e) => {
                // Failed to create or write to the new file.
                eprintln!("Error: Could not create state file '{}' with default value: {}. Proceeding with in-memory default.", STATE_FILENAME, e);
                // Fallback to None, new() will use unwrap_or(0) for in-memory state.
                return None;
            }
        }
    }

    match File::open(STATE_FILENAME) {
        Ok(mut file) => {
            let mut contents = String::new();
            if file.read_to_string(&mut contents).is_ok() {
                // Trim whitespace and parse to i32
                contents.trim().parse::<i32>().ok()
            } else {
                eprintln!("Error: Could not read from state file '{}'.", STATE_FILENAME);
                None
            }
        }
        Err(e) => {
            if e.kind() != ErrorKind::NotFound {
                 eprintln!("Error: Could not open state file '{}' for reading: {}", STATE_FILENAME, e);
            }
            None
        }
    }
}

// Helper function to save the value to the file
fn save_value_to_file(value: i32) -> std::io::Result<()> {
    let mut file = OpenOptions::new()
        .write(true)
        .create(true)
        .truncate(true)
        .open(STATE_FILENAME)?;
    file.write_all(value.to_string().as_bytes())?;
    Ok(())
}


// 1. Define the application's state
struct CounterApp {
    value: i32, // The current value of the counter
    val_history: Option<i32>, // Stores the value before the last update
}

// 2. Define the messages the application can handle
#[derive(Debug, Clone, Copy)]
enum Message {
    IncrementPressed,
    DecrementPressed,
    ResetPressed,
}

// This impl block is specifically for CounterApp's own associated functions
impl CounterApp {
    fn settings() -> Settings<()> {
        Settings {
            window: iced::window::Settings {
                size: Size { width: 360.0, height: 360.0 },
                resizable: true,
                ..iced::window::Settings::default()
            },
            flags: (),
            ..Settings::default()
        }
    }
}

// 3. Implement the Sandbox trait for our application state
impl Sandbox for CounterApp {
    type Message = Message;

    fn new() -> Self {
        let initial_value = load_value_from_file().unwrap_or(0);
        // Initialize val_history as None, as there's no previous state on fresh start
        Self { value: initial_value, val_history: None }
    }

    fn title(&self) -> String {
        String::from("Persistent Counter with History") // Updated title
    }

    fn update(&mut self, message: Message) {
        // Store the current value as history BEFORE updating it
        self.val_history = Some(self.value);
        // For debugging:
        // if let Some(history) = self.val_history {
        //     println!("Stored history: {}", history);
        // }


        let mut value_changed_for_saving = true; // Flag for file saving logic

        match message {
            Message::IncrementPressed => {
                self.val_history = Some(self.value);
                self.value += 1;
                // println!("Value incremented to: {}", self.value); // For debugging
            }
            Message::DecrementPressed => {
                self.val_history = Some(self.value);
                self.value -= 1;
                // println!("Value decremented to: {}", self.value); // For debugging
            }
            Message::ResetPressed => {
                // Check if value actually changes for the purpose of file saving.
                // History is already updated above.
                if self.value == 0 {
                    value_changed_for_saving = false;
                }
                self.val_history = Some(self.value);
                self.value = 0;
                // println!("Value reset to: {}", self.value); // For debugging
            }
        }

        // If the value changed (for the purpose of persistence), save it to the file
        if value_changed_for_saving {
            if let Err(e) = save_value_to_file(self.value) {
                eprintln!("Error: Could not save state to file '{}': {}", STATE_FILENAME, e);
            }
        }
    }

    fn view(&self) -> Element<Message> {
        let increment_button = button(
            text("+")
                .size(40) // Set the size of the "+" text
                .width(Length::Fill) // Make the text widget fill the available horizontal space within the button
                .horizontal_alignment(iced::alignment::Horizontal::Center) // Center the text horizontally
                .vertical_alignment(iced::alignment::Vertical::Center)   // Center the text vertically
        ).on_press(Message::IncrementPressed)
        .padding(20) // Padding inside the button, around the text widget
        .width(Length::Fixed(120.0)); // Fixed width for the button itself

        let decrement_button = button(text("  -  ").size(20))
            .on_press(Message::DecrementPressed)
            .padding(10);

        let reset_button = button(text(" Reset ").size(20))
            .on_press(Message::ResetPressed)
            .padding(10);

        let value_text = text(self.value.to_string()).size(100);

        // Optionally, display history (for debugging or if needed in UI)
        // let history_text_val = self.val_history.map_or_else(|| "N/A".to_string(), |h| h.to_string());
        // let history_display = text(format!("Last: {}", history_text_val)).size(20);

        let control_buttons_row = row![decrement_button, reset_button]
            .spacing(20)
            .align_items(Alignment::Center);

        let content_column = column![
            value_text,
            // history_display, // Uncomment to show history in UI
            increment_button,
            control_buttons_row
        ]
        .spacing(30)
        .align_items(Alignment::Center);

        container(content_column)
            .width(Length::Fill)
            .height(Length::Fill)
            .center_x()
            .center_y()
            .into()
    }
}

// 4. Main function to run the application
pub fn main() -> iced::Result {
    CounterApp::run(CounterApp::settings())
}
