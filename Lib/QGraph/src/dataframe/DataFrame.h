#pragma once

namespace Quantum {
namespace  QGraph {
    class DataFrame {
            public:
                DataFrame() = default;
                ~DataFrame() = default;

                // Add methods to manipulate and access the DataFrame
                void addColumn(const std::string& name, const std::vector<double>& data);
                void removeColumn(const std::string& name);
                std::vector<double> getColumn(const std::string& name) const;

            private:
                std::unordered_map<std::string, std::vector<double>> columns_;
            };

        } 
}