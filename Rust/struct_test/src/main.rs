#[derive(Debug)]
struct Rectangle {
    width: u32,
    length: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.length
    }
    
    fn square(size: u32) -> Rectangle {
        Rectangle {
            width: size,
            length: size,
        }
    }
}

fn main() {
    let rect = Rectangle {
        width: 22,
        length: 33,
    };
    
    // use :: to call function square
    let sqr = Rectangle::square(233);
    
    println!("{}", rect.area());
    println!("{:#?}", rect);
    println!("{}", sqr.area());
    println!("{:#?}", sqr);
}
