let map = (f: 'a => 'b, value: option('a)) : option('b) =>
  switch value {
  | Some(v) => Some(f(v))
  | None => None
  };

let flatMap = (f: 'a => option('b), value: option('a)) : option('b) =>
  switch value {
  | Some(v) => f(v)
  | None => None
  };

let filter = (f: 'a => bool, value: option('a)) : option('a) =>
  switch value {
  | Some(v) => f(v) ? Some(v) : None
  | None => None
  };

let getOrElse = (default: 'a, value: option('a)) : 'a =>
  switch value {
  | Some(v) => v
  | None => default
  };

let andThen = (fn: 'a => unit, value: option('a)) : unit =>
  switch value {
  | Some(v) => fn(v)
  | None => ()
  };
