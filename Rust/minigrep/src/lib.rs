use std::fs;
use std::error::Error;


pub struct Config {
    query: String,
    filename: String,
    case_sensitive: bool,
}

impl Config {
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("arguments are less than 3");
        }
        
        let query = args[1].clone();
        let filename = args[2].clone();
        let mut case_sensitive = false;
        if args.len() > 3 && args[3].contains("-c") {
            case_sensitive = true;
        }

        Ok(Config{query, filename, case_sensitive})
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    // println!("Search for {}", config.query);
    // println!("In file {}", config.filename);
    // println!("with text:\n{}", contents);
    
    let contents = fs::read_to_string(config.filename)?;
    for line in search(&config.query, &contents, config.case_sensitive) {
        println!("{}", line);
    }
    Ok(())
}

pub fn search<'a>(qeury: &str, contents: &'a str, case_sensitive: bool) -> Vec<&'a str> {
    let mut results = Vec::new();
    for line in contents.lines() {
        if case_sensitive && line.to_lowercase().contains(&qeury.to_lowercase()) {
            results.push(line);
        } else if line.contains(qeury) {
            results.push(line);
        }
    }
    results
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn one_result() {
        let query = "falca";
        let contents = "\
aaa
bbb
ccc falca
ddd
eee";
        let res = search(query, contents, false);
        assert_eq!(vec!["ccc falca"], res);
        println!("<one_result> test passed: {}", res[0])
    }

    #[test]
    fn case_sensitive() {
        let query = "FaLcA";
        let contents = "\
aaa
bbb
ccc falca
ddd
eee";
        let res = search(query, contents, true);
        assert_eq!(vec!["ccc falca"], res);
        println!("<case_sensitive> test passed: {}", res[0])
    }
}
