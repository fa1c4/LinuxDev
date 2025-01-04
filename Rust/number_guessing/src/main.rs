use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("Number Guessing Game by fa1c4");
    println!("-----------------------------");

    let secret_number = rand::thread_rng().gen_range(1, 101);


    loop {
        let mut guess_num = String::new();

        io::stdin().read_line(&mut guess_num).expect("error while reading line");
        // io::Result = Ok | Err(with error information)
    
        let guessing: u32 = match guess_num.trim().parse() {
            Ok(num) => num,
            Err(_error_msg) => {
                println!("input again");
                continue;
            },
        };
    
        println!("your guessing number is {}", guessing);
    
        match guessing.cmp(&secret_number) {
            Ordering::Less => println!("smaller"),
            Ordering::Greater => println!("Bigger"),
            Ordering::Equal => {
                println!("You are correct");
                break;
            },
        }
    }
}
