template<class UnaryFunction>
void recursive_iterate(const json& j, UnaryFunction f)
{
       for(auto it = j.begin(); it != j.end(); ++it)
       {
           if (it->is_structured())
           {
               recursive_iterate(*it, f);
           }
           else
           {
               f(it);
           }
       }
}

int main()
{
       json j = {{"one", 1}, {"two", 2}, {"three", {"three.one", 3.1}}};
       recursive_iterate(j, [](json::const_iterator it){
           std::cout << *it << std::endl;
       });
}
